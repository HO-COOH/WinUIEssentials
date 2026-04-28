#include "pch.h"
#include "TableD2DContent.h"
#include "D2DPrimitiveHelper.h"
#include <dxgi1_3.h>
#include <numeric>
#include <cmath>
#include "Table.h"
#include "Easing.hpp"
#include "HighResTimer.h"

TableD2DContent::TableD2DContent() : m_columnWidths(std::size(TableTestData::Columns))
{
	for (auto& w : m_columnWidths)
		w.store(TableConstants::ColumnWidth, std::memory_order_relaxed);

	auto dxgiDevice = m_d3dDevice.as<IDXGIDevice1>();
	winrt::check_hresult(dxgiDevice->SetMaximumFrameLatency(1));

	auto d2d1Factory = DirectN::CreateD2D1Factory();
	auto d2d1Device = DirectN::GetD2D1Device(d2d1Factory.get(), m_d3dDevice.get());
	winrt::check_hresult(d2d1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_d2dContext.put()));

	winrt::check_hresult(m_dwriteFactory->CreateTextFormat(
		L"Segoe UI Semibold",
		nullptr,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		TableConstants::HeaderFontSize,
		L"en-US",
		m_headerTextFormat.put()
	));
	winrt::check_hresult(m_dwriteFactory->CreateTextFormat(
		L"Segoe UI",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		TableConstants::CellFontSize,
		L"en-US",
		m_cellTextFormat.put()
	));
	m_textLayoutCache.SetFormat(m_cellTextFormat.get());

	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), m_textBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x0F / static_cast<float>(0xFF)), m_backgroundBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x2F / static_cast<float>(0xFF)), m_alternateBackgroundBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x4cc2ff), m_pillBrush.put()));
}

TableD2DContent::~TableD2DContent()
{
	Stop();
}

void TableD2DContent::Initialize(winrt::WinUI3Package::implementation::Table& table)
{
	m_table_ref = &table;
	m_swapChain.Set(m_d3dDevice.get(), table);
	m_dispatcher = table.DispatcherQueue();
	m_drawThread = std::thread([this] { drawThreadProc(); });
}

void TableD2DContent::Stop()
{
	if (!m_drawThread.joinable())
		return;
	m_stopRequested.store(true, std::memory_order_release);
	m_drawRequest.store(true, std::memory_order_release);
	m_drawRequest.notify_all();
	m_drawThread.join();
}

void TableD2DContent::RequestDraw()
{
	m_drawRequest.store(true, std::memory_order_release);
	m_drawRequest.notify_one();
}

void TableD2DContent::SizeChanged(
	winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender,
	winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e)
{
	m_swapChain.SizeChanged(sender, e);
	m_swapChainDirty.store(true, std::memory_order_release);
	RequestDraw();
}

void TableD2DContent::SetScrollOffsetX(float x)
{
	m_scrollOffsetX.store(x, std::memory_order_relaxed);
}

void TableD2DContent::SetScrollOffsetY(float y)
{
	m_scrollOffsetY.store(y, std::memory_order_relaxed);
}

float TableD2DContent::ScrollOffsetX() const
{
	return m_scrollOffsetX.load(std::memory_order_relaxed);
}

float TableD2DContent::ScrollOffsetY() const
{
	return m_scrollOffsetY.load(std::memory_order_relaxed);
}

void TableD2DContent::StartSmoothScrollY(float targetY)
{
	m_smoothScrollTargetY.store(targetY, std::memory_order_relaxed);
	m_pendingScrollRequest.startY = m_scrollOffsetY.load(std::memory_order_relaxed);
	m_pendingScrollRequest.endY = targetY;
	m_pendingScrollRequest.startTime = std::chrono::steady_clock::now();
	//release: publishes the fields above to the draw thread
	m_pendingScrollRequest.isPending.store(true, std::memory_order_release);
	RequestDraw();
}

void TableD2DContent::StopSmoothScroll()
{
	m_isScrolling.store(false, std::memory_order_release);
}

bool TableD2DContent::IsScrolling() const
{
	return m_isScrolling.load(std::memory_order_acquire);
}

float TableD2DContent::SmoothScrollTargetY() const
{
	return m_smoothScrollTargetY.load(std::memory_order_relaxed);
}

float TableD2DContent::ColumnWidth(int column) const
{
	return m_columnWidths[column].load(std::memory_order_relaxed);
}

void TableD2DContent::SetColumnWidth(int column, float width)
{
	m_columnWidths[column].store(width, std::memory_order_relaxed);
}

int TableD2DContent::HoveredResizeColumn() const
{
	return m_hoveredResizeColumn.load(std::memory_order_relaxed);
}

bool TableD2DContent::SetHoveredResizeColumn(int index)
{
	return m_hoveredResizeColumn.exchange(index, std::memory_order_relaxed) != index;
}

int TableD2DContent::GetResizeColumnIndex(float x) const
{
	float currentColumnEndX = -m_scrollOffsetX.load(std::memory_order_relaxed);
	for (size_t i = 0; i < m_columnWidths.size(); ++i)
	{
		currentColumnEndX += m_columnWidths[i].load(std::memory_order_relaxed);
		if (std::abs(x - currentColumnEndX) <= TableConstants::ResizeHotZoneDelta)
			return static_cast<int>(i);
	}
	return TableConstants::ResizeColumnIndexNone;
}

float TableD2DContent::GetViewportHeight() const
{
	return m_swapChain.CurrentSize.Height - TableConstants::RowHeight;
}

float TableD2DContent::GetViewportWidth() const
{
	return m_swapChain.CurrentSize.Width;
}

float TableD2DContent::TotalContentWidth() const
{
	float total = 0.f;
	for (auto const& w : m_columnWidths)
		total += w.load(std::memory_order_relaxed);
	return total;
}

int TableD2DContent::DataCount() const
{
	return m_data.Count();
}

D2D1_ROUNDED_RECT TableD2DContent::getResizePillRect(std::vector<float> const& columnWidths, int column, float scrollOffsetX) const
{
	auto const columnEndX = std::accumulate(columnWidths.begin(), columnWidths.begin() + column + 1, -scrollOffsetX);
	auto const rawColumnEndX = columnEndX * m_swapChain.Scale;
	auto const left = rawColumnEndX - TableConstants::ResizeHotZoneDelta * m_swapChain.Scale;

	return D2D1_ROUNDED_RECT
	{
		.rect = D2D_RECT_F
		{
			.left = left,
			.top = TableConstants::PillPadding * m_swapChain.Scale,
			.right = left + TableConstants::ResizeHotZoneDelta * m_swapChain.Scale,
			.bottom = (TableConstants::RowHeight - TableConstants::PillPadding) * m_swapChain.Scale
		},
		.radiusX = TableConstants::PillCornerRadius * m_swapChain.Scale,
		.radiusY = TableConstants::PillCornerRadius * m_swapChain.Scale
	};
}

void TableD2DContent::drawThreadProc()
{
	HighResTimer highResTimer;
	while(true)
	{
		if (!m_isScrolling.load(std::memory_order_acquire))
		{
			highResTimer = false;
			m_drawRequest.wait(false, std::memory_order_acquire);
		}

		if (m_stopRequested.load(std::memory_order_acquire))
			break;

		m_drawRequest.store(false, std::memory_order_release);

		//pick up a new scroll request if one arrived.
		//acquire: pairs with release store in StartSmoothScrollY so the
		//field writes there are visible here.
		if (m_pendingScrollRequest.isPending.exchange(false, std::memory_order_acquire))
		{
			m_activeScrollRequest.startY = m_pendingScrollRequest.startY;
			m_activeScrollRequest.endY = m_pendingScrollRequest.endY;
			m_activeScrollRequest.startTime = m_pendingScrollRequest.startTime;
			m_isScrolling.store(true, std::memory_order_release);
		}

		//advance the scroll animation for this frame
		if (m_isScrolling.load(std::memory_order_acquire))
		{
			highResTimer = true;

			auto const progress = m_activeScrollRequest.Progress();
			auto const eased = EasedProgress(progress, 5);
			bool const done = progress >= 1.0;
			auto const newY = done ? 
				m_activeScrollRequest.endY: 
				m_activeScrollRequest.startY + (m_activeScrollRequest.endY - m_activeScrollRequest.startY) * static_cast<float>(eased);
			m_dispatcher.TryEnqueue([this, newY] { m_table_ref->updateVerticalScrollBar(newY); });
			m_scrollOffsetY.store(newY, std::memory_order_relaxed);
			if (done)
				m_isScrolling.store(false, std::memory_order_release);
		}

		if (m_swapChainDirty.exchange(false, std::memory_order_acq_rel))
			m_swapChain.SetTarget(m_d2dContext.get());

		draw();

		//pace the animation without pegging the CPU
		if (m_isScrolling.load(std::memory_order_acquire) && !m_stopRequested.load(std::memory_order_acquire))
			std::this_thread::sleep_for(std::chrono::milliseconds{ 4 });
	}
}

void TableD2DContent::draw()
{
	if (!m_swapChain.get())
		return;
	if (m_swapChain.CurrentSize.Width <= 0 || m_swapChain.CurrentSize.Height <= 0)
		return;

	std::vector<float> columnWidths;
	columnWidths.reserve(m_columnWidths.size());
	for (auto const& w : m_columnWidths)
		columnWidths.push_back(w.load(std::memory_order_relaxed));
	int const hoveredResizeColumn = m_hoveredResizeColumn.load(std::memory_order_relaxed);

	auto const scrollOffsetX = m_scrollOffsetX.load(std::memory_order_relaxed);
	auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);

	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(0, 0));
	drawRows(columnWidths, scrollOffsetX, scrollOffsetY);
	drawHeader(columnWidths, hoveredResizeColumn, scrollOffsetX);
	m_d2dContext->EndDraw();

	DXGI_PRESENT_PARAMETERS presentParameters{};
	winrt::check_hresult(m_swapChain->Present1(0, DXGI_PRESENT_RESTART, &presentParameters));
}

void TableD2DContent::drawHeader(std::vector<float> const& columnWidths, int hoveredResizeColumn, float scrollOffsetX)
{
	auto const scale = m_swapChain.Scale;
	auto currentX = -scrollOffsetX * scale;
	for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
	{
		auto const rawColumnWidth = columnWidths[column] * scale;
		m_d2dContext->DrawTextW(
			TableTestData::Columns[column],
			static_cast<uint32_t>(std::wstring_view{ TableTestData::Columns[column] }.size()),
			m_headerTextFormat.get(),
			D2D1_RECT_F
			{
				.left = currentX,
				.top = 0,
				.right = currentX + rawColumnWidth,
				.bottom = 30 * scale
			},
			m_textBrush.get()
		);

		if (m_sortColumnIndex == static_cast<int>(column))
		{
			//draw sort indicator here
		}

		if (hoveredResizeColumn != TableConstants::ResizeColumnIndexNone)
		{
			auto const pillRect = getResizePillRect(columnWidths, hoveredResizeColumn, scrollOffsetX);
			m_d2dContext->FillRoundedRectangle(&pillRect, m_pillBrush.get());
		}

		D2DPrimitiveHelper::DrawVerticalLine(
			m_d2dContext.get(),
			currentX + rawColumnWidth - 1,
			4 * scale,
			(4 + TableConstants::HeaderFontSize) * scale,
			m_textBrush.get()
		);
		currentX += rawColumnWidth;
	}
}

void TableD2DContent::drawRows(std::vector<float> const& columnWidths, float scrollOffsetX, float scrollOffsetY)
{
	auto const rawRowHeight = TableConstants::RowHeight * m_swapChain.Scale;

	int const first = (std::max)(0, static_cast<int>(scrollOffsetY / rawRowHeight));
	int const last = (std::min)(m_data.Count() - 1, static_cast<int>((scrollOffsetY + m_swapChain.CurrentSize.Height * m_swapChain.Scale) / rawRowHeight));
	for (int row = first; row <= last; ++row)
	{
		auto& rowData = m_data[row];
		auto const rowY = (row + 1) * rawRowHeight - scrollOffsetY;

		//draw background
		D2D1_ROUNDED_RECT const rect
		{
			.rect = D2D1::RectF(0, rowY, m_swapChain.CurrentSize.Width * m_swapChain.Scale, rowY + rawRowHeight),
			.radiusX = TableConstants::CornerRadius * m_swapChain.Scale,
			.radiusY = TableConstants::CornerRadius * m_swapChain.Scale
		};
		m_d2dContext->FillRoundedRectangle(
			&rect,
			(row % 2 == 0) ? m_backgroundBrush.get() : m_alternateBackgroundBrush.get()
		);

		//draw columns
		auto const scale = m_swapChain.Scale;
		auto currentX = -scrollOffsetX * scale;
		for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
		{
			auto const rawColumnWidth = columnWidths[column] * scale;
			auto const header = m_data.Header()[column];
			auto const& columnData = rowData[column];
			auto const& layoutCache = m_textLayoutCache.GetOrCreate(row, column, columnData, rawColumnWidth, rawRowHeight);
			winrt::check_hresult(layoutCache->SetParagraphAlignment(header.VerticalAlignment));
			winrt::check_hresult(layoutCache->SetTextAlignment(header.HorizontalAlignment));
			m_d2dContext->DrawTextLayout(
				D2D1::Point2F(currentX, rowY),
				layoutCache,
				m_textBrush.get()
			);
			currentX += rawColumnWidth;
		}

		//draw line
		D2DPrimitiveHelper::DrawHorizontalLine(
			m_d2dContext.get(),
			0,
			m_swapChain.CurrentSize.Width * m_swapChain.Scale,
			rowY + rawRowHeight,
			m_textBrush.get()
		);
	}
}
