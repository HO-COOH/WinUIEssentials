#include "pch.h"
#include "TableD2DContent.h"
#include "D2DPrimitiveHelper.h"
#include <dxgi1_3.h>
#include <numeric>
#include <cmath>
#include <algorithm>
#include "Table.h"
#include "Easing.hpp"
#include "HighResTimer.h"

TableD2DContent::TableD2DContent(winrt::PackageRoot::implementation::Table& table) : 
	m_dispatcher{ table },
	m_table_ref{ table }, 
	m_drawThread{ [this] { drawThreadProc(); } }
{
	m_swapChain.Set(m_d3dDevice.get(), table);

	auto d2d1Device = DirectN::GetD2D1Device(d2d1Factory.get(), m_d3dDevice.get());
	winrt::check_hresult(d2d1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_d2dContext.put()));

	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), m_textBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x7F / static_cast<float>(0xFF)), m_tableLines.m_brush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x0F / static_cast<float>(0xFF)), m_backgroundBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x2F / static_cast<float>(0xFF)), m_alternateBackgroundBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x4cc2ff), m_pillBrush.put()));
	winrt::check_hresult(m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x103c4c), m_hoverBrush.put()));
}

TableD2DContent::~TableD2DContent()
{
	Stop();
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

void TableD2DContent::RequestDraw(bool redraw)
{
	m_drawRequest.store(true, std::memory_order_release);
	if (redraw)
		m_fullRedrawNeeded.store(true, std::memory_order_relaxed);
	m_drawRequest.notify_one();
}

void TableD2DContent::SizeChanged(
	winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender,
	winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e)
{
	if (!m_swapChain.SizeChanged(sender, e))
		return;
	m_swapChainDirty.store(true, std::memory_order_release);
	m_fullRedrawNeeded.store(true, std::memory_order_release);
	updateScrollOffsets();
	RequestDraw();
}

void TableD2DContent::updateScrollOffsets()
{
	auto const totalHeight = m_data.Count() * TableConstants::RowHeight;
	auto const maxScrollY = (std::max)(0.f, totalHeight - GetViewportHeight());
	auto const maxScrollX = (std::max)(0.f, TotalContentWidth() - GetViewportWidth());

	m_scrollOffsetY.store(std::clamp(m_scrollOffsetY.load(std::memory_order_relaxed), 0.f, maxScrollY), std::memory_order_relaxed);
	m_scrollOffsetX.store(std::clamp(m_scrollOffsetX.load(std::memory_order_relaxed), 0.f, maxScrollX), std::memory_order_relaxed);
}

void TableD2DContent::CompositionScaleChanged(
	winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender)
{
	if (!m_swapChain.CompositionScaleChanged(sender))
		return;
	m_swapChainDirty.store(true, std::memory_order_release);
	m_fullRedrawNeeded.store(true, std::memory_order_release);
	RequestDraw();
}

void TableD2DContent::SetScrollOffsetX(float x)
{
	m_scrollOffsetX.store(x, std::memory_order_relaxed);
	m_fullRedrawNeeded.store(true, std::memory_order_release);
}

void TableD2DContent::SetScrollOffsetY(float y)
{
	m_scrollOffsetY.store(y, std::memory_order_relaxed);
	m_fullRedrawNeeded.store(true, std::memory_order_release);
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
	m_fullRedrawNeeded.store(true, std::memory_order_release);
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


int TableD2DContent::HoveredResizeColumn() const
{
	return m_hoveredResizeColumn.load(std::memory_order_relaxed);
}

bool TableD2DContent::SetHoveredResizeColumn(int index)
{
	bool const changed = m_hoveredResizeColumn.exchange(index, std::memory_order_relaxed) != index;
	if (changed)
		m_fullRedrawNeeded.store(true, std::memory_order_release);
	return changed;
}

int TableD2DContent::GetResizeColumnIndex(float x) const
{
	return m_columnWidthManager.GetColumnIndexFromX(x, -m_scrollOffsetX.load(std::memory_order_relaxed));
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
	return m_initialSizing.load(std::memory_order_relaxed)? m_swapChain.CurrentSize.Width : m_columnWidthManager.SumColumnWidth(std::size(TableTestData::Columns));
}

int TableD2DContent::DataCount() const
{
	return m_data.Count();
}

void TableD2DContent::SetHover(float y)
{
	int newRow;
	if (y <= TableConstants::RowHeight)
		newRow = TableConstants::HoveredRowNone;
	else
	{
		auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);
		newRow = static_cast<int>((y + scrollOffsetY) / TableConstants::RowHeight) - 1;
	}
	if (std::exchange(m_hoveredRow, newRow) != newRow)
		RequestDraw();
}

D2D1_ROUNDED_RECT TableD2DContent::getResizePillRect(int column, float scrollOffsetX) const
{
	auto const columnEndX = m_columnWidthManager.SumColumnWidth(column + 1, -scrollOffsetX);
	auto const rawColumnEndX = columnEndX * m_swapChain.Scale;

	auto const scaledPillWidth = TableConstants::PillWidth * m_swapChain.Scale;

	return D2D1_ROUNDED_RECT
	{
		.rect = D2D_RECT_F
		{
			.left = rawColumnEndX - scaledPillWidth,
			.top = TableConstants::PillPaddingY * m_swapChain.Scale,
			.right = rawColumnEndX + scaledPillWidth,
			.bottom = (TableConstants::RowHeight - TableConstants::PillPaddingY) * m_swapChain.Scale
		},
		.radiusX = TableConstants::PillCornerRadius * m_swapChain.Scale,
		.radiusY = TableConstants::PillCornerRadius * m_swapChain.Scale
	};
}

D2D_RECT_F TableD2DContent::getRowRect(int row, float scrollOffsetY, float scale) const
{
	auto const rawRowHeight = TableConstants::RowHeight * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rowTop = (row + 1) * rawRowHeight - scrollOffsetY * scale;
	return { 0, rowTop, rawWidth, rowTop + rawRowHeight };
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

			//only call dispatcher when the scrollBar position actually changed
			if (auto const newYFloor = static_cast<int>(newY); newYFloor != m_cachedScrollBarY)
			{
				m_dispatcher.TryEnqueue([this, newY] { m_table_ref.updateVerticalScrollBar(newY); });
				m_cachedScrollBarY = newYFloor;
			}

			m_scrollOffsetY.store(newY, std::memory_order_relaxed);
			m_fullRedrawNeeded.store(true, std::memory_order_release);
			if (done)
				m_isScrolling.store(false, std::memory_order_release);
		}

		if (m_swapChainDirty.exchange(false, std::memory_order_acq_rel))
		{
			m_swapChain.SetTarget(m_d2dContext.get());
			m_fullRedrawNeeded.store(true, std::memory_order_release);
		}

		if (std::exchange(m_textLayoutCache.Scale, m_swapChain.Scale) != m_swapChain.Scale)
		{
			rebuildTextFormatsForScale();
			m_fullRedrawNeeded.store(true, std::memory_order_release);
		}

		draw();
	}
}

void TableD2DContent::rebuildTextFormatsForScale()
{
	m_textLayoutCache.CreateHeaderTextFormat(
		L"Segoe UI Semibold",
		nullptr,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		TableConstants::HeaderFontSize,
		L"en-US"
	);
	m_textLayoutCache.CreateCeilTextFormat(
		L"Segoe UI",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		TableConstants::CellFontSize,
		L"en-US"
	);
	m_textLayoutCache.Clear();
}

void TableD2DContent::draw()
{
	if (!m_swapChain.get())
		return;
	if (m_swapChain.CurrentSize.Width <= 0 || m_swapChain.CurrentSize.Height <= 0)
		return;

	int const hoveredResizeColumn = m_hoveredResizeColumn.load(std::memory_order_relaxed);
	auto const scrollOffsetX = m_scrollOffsetX.load(std::memory_order_relaxed);
	auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);
	auto const scale = m_swapChain.Scale;

	bool const fullRedraw = m_fullRedrawNeeded.exchange(false, std::memory_order_acq_rel);

	if (fullRedraw)
		drawFull(scrollOffsetX, scrollOffsetY, hoveredResizeColumn, m_hoveredRow, scale);
	else if (m_hoveredRow != m_prevHoveredRow)
		drawPartialHover(m_prevHoveredRow, m_hoveredRow, scrollOffsetX, scrollOffsetY, scale);

	m_prevHoveredRow = m_hoveredRow;
}

void TableD2DContent::drawFull(float scrollOffsetX, float scrollOffsetY, int hoveredResizeColumn, int hoveredRow, float scale)
{
	auto const rawViewportWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawViewportHeight = m_swapChain.CurrentSize.Height * scale;
	auto const rawRowHeight = TableConstants::RowHeight * scale;
	auto const rawHeaderHeight = TableConstants::HeaderHeight * scale;
	m_tableLines.Rebuild(rawViewportWidth, rawViewportHeight, rawRowHeight, rawHeaderHeight);

	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(0, 0));

	m_textLayoutCache.SetNumColumns(std::size(TableTestData::Columns));
	drawRows(scrollOffsetX, scrollOffsetY, hoveredRow);
	auto const rawDataBottomY = rawHeaderHeight + m_data.Count() * rawRowHeight - scrollOffsetY * scale;
	m_tableLines.Draw(m_d2dContext.get(), scrollOffsetY * scale, rawDataBottomY - 1);
	drawHeader(hoveredResizeColumn, scrollOffsetX);
	m_d2dContext->EndDraw();

	DXGI_PRESENT_PARAMETERS presentParameters{};
	winrt::check_hresult(m_swapChain->Present1(0, 0, &presentParameters));
	Frames.fetch_add(1, std::memory_order_relaxed);

	if (m_initialSizing && m_data.Count() > 0)
	{
		m_columnWidthManager.GetInitialColumnWidth(m_swapChain.CurrentSize.Width, m_swapChain.Scale);
		m_initialSizing = false;
		m_fullRedrawNeeded.store(true, std::memory_order_release);
		RequestDraw();
	}
}

void TableD2DContent::drawPartialHover(int oldRow, int newRow, float scrollOffsetX, float scrollOffsetY, float scale)
{
	auto const rawRowHeight = TableConstants::RowHeight * scale;
	auto const rawHeaderHeight = TableConstants::HeaderHeight * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawHeight = m_swapChain.CurrentSize.Height * scale;
	auto const rawScrollY = scrollOffsetY * scale;
	auto const rawCornerRadius = TableConstants::CornerRadius * scale;
	auto const dataCount = m_data.Count();

	struct DirtyRow
	{
		int row;
		D2D_RECT_F rowRect;
	};
	DirtyRow dirtyRows[2];
	int dirtyCount = 0;

	auto addIfVisible = [&](int row)
	{
		if (row == TableConstants::HoveredRowNone || row < 0 || row >= dataCount)
			return;
		auto rowRect = getRowRect(row, scrollOffsetY, scale);
		rowRect.top = (std::max)(rowRect.top, rawHeaderHeight);
		rowRect.bottom = (std::min)(rowRect.bottom, rawHeight);
		if (rowRect.bottom <= rowRect.top)
			return;
		dirtyRows[dirtyCount++] = { row, rowRect };
	};
	addIfVisible(oldRow);
	if (newRow != oldRow)
		addIfVisible(newRow);

	if (dirtyCount == 0)
		return;

	auto const rawDataBottomY = rawHeaderHeight + dataCount * rawRowHeight - rawScrollY;

	m_d2dContext->BeginDraw();
	for (int i = 0; i < dirtyCount; ++i)
	{
		auto const& dirty = dirtyRows[i];
		m_d2dContext->PushAxisAlignedClip(
			D2D1::RectF(0, dirty.rowRect.top + 1 * scale, rawWidth, dirty.rowRect.bottom - 1 * scale),
			D2D1_ANTIALIAS_MODE_ALIASED
		);
		m_d2dContext->Clear(D2D1::ColorF(0, 0));

		if (dirty.row == newRow)
		{
			D2D1_ROUNDED_RECT const fill
			{
				.rect = D2D1::RectF(dirty.rowRect.left, dirty.rowRect.top + 1 * scale, dirty.rowRect.right, dirty.rowRect.bottom - 1 * scale),
				.radiusX = rawCornerRadius,
				.radiusY = rawCornerRadius
			};
			m_d2dContext->FillRoundedRectangle(&fill, m_hoverBrush.get());
		}

		drawRowCells(dirty.row, dirty.rowRect.top, scrollOffsetX, scale);
		m_d2dContext->PopAxisAlignedClip();
	}
	m_d2dContext->EndDraw();

	RECT rects[2];
	for (int i = 0; i < dirtyCount; ++i)
	{
		auto const& dirty = dirtyRows[i];
		rects[i] = RECT{
			.left = 0,
			.top = static_cast<LONG>(std::floor(dirty.rowRect.top)),
			.right = static_cast<LONG>(std::ceil(rawWidth)),
			.bottom = static_cast<LONG>(std::ceil(dirty.rowRect.bottom))
		};
	}

	DXGI_PRESENT_PARAMETERS const params
	{
		.DirtyRectsCount = static_cast<UINT>(dirtyCount),
		.pDirtyRects = rects
	};
	winrt::check_hresult(m_swapChain->Present1(0, 0, &params));
	Frames.fetch_add(1, std::memory_order_relaxed);
}

void TableD2DContent::drawHeader(int hoveredResizeColumn, float scrollOffsetX)
{
	auto const scale = m_swapChain.Scale;
	auto currentX = -scrollOffsetX * scale;
	auto rawHeaderHeight = TableConstants::HeaderHeight * m_swapChain.Scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
	{
		auto const rawColumnWidth = m_initialSizing? (std::numeric_limits<float>::max)() : m_columnWidthManager.Get(column) * scale;
		if (currentX + rawColumnWidth > 0 || m_initialSizing)
		{
			if (currentX >= rawWidth && !m_initialSizing) //early return only if not initialize sizing 
				return;

			auto header = m_data.Header()[column];
			auto layout = m_textLayoutCache.GetOrCreate(column, TableTestData::Columns[column], rawColumnWidth, rawHeaderHeight, header.HeaderHorizontalAlignment, header.HeaderVerticalAlignment);
			if (!m_initialSizing)
				m_d2dContext->DrawTextLayout({ currentX, 0 }, layout, m_textBrush.get());

			if (m_sortColumnIndex == static_cast<int>(column))
			{
				//draw sort indicator here
			}


			if (column != std::size(TableTestData::Columns) - 1)
			{
				//the resize handle do not needs to be drawn for the last column
				D2DPrimitiveHelper::DrawVerticalLine(
					m_d2dContext.get(),
					currentX + rawColumnWidth - 1,
					TableConstants::PillPaddingY * scale,
					(TableConstants::RowHeight - TableConstants::PillPaddingY) * scale,
					hoveredResizeColumn == column ? m_pillBrush.get() : m_textBrush.get()
				);
			}
		}
		currentX += rawColumnWidth;
	}
}

void TableD2DContent::drawRows(float scrollOffsetX, float scrollOffsetY, int hoveredRow)
{
	auto const scale = m_swapChain.Scale;
	auto const rawScrollOffsetY = scrollOffsetY * scale;
	auto const rawBottom = m_swapChain.CurrentSize.Height * scale;
	auto const rawRight = m_swapChain.CurrentSize.Width * scale;
	m_d2dContext->PushAxisAlignedClip(D2D1::RectF(0, TableConstants::HeaderHeight * scale, rawRight, rawBottom), D2D1_ANTIALIAS_MODE_ALIASED);
	auto const rawRowHeight = TableConstants::RowHeight * scale;
	int const first = (std::max)(0, static_cast<int>(rawScrollOffsetY / rawRowHeight));
	int const last = (std::min)(m_data.Count() - 1, static_cast<int>((rawScrollOffsetY + rawBottom) / rawRowHeight));

	auto rawCornerRadius = TableConstants::CornerRadius * scale;

	for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
	{
		auto const header = m_data.Header()[column];
		m_textLayoutCache.SetColumnFormat(column, header.HorizontalAlignment, header.VerticalAlignment);
	}

	for (int row = first; row <= last; ++row)
	{
		auto const rowRect = getRowRect(row, scrollOffsetY, scale);

		if (row == hoveredRow)
		{
			D2D1_ROUNDED_RECT const fill
			{
				.rect = D2D1::RectF(rowRect.left, rowRect.top + 1, rowRect.right, rowRect.bottom - 1),
				.radiusX = rawCornerRadius,
				.radiusY = rawCornerRadius
			};
			m_d2dContext->FillRoundedRectangle(&fill, m_hoverBrush.get());
		}
		else
		{
			//draw default background
			//m_d2dContext->FillRectangle(
			//	D2D1::RectF(rawCornerRadius, rowRect.top, rowRect.right - rawCornerRadius, rowRect.bottom),
			//	(row % 2 == 0) ? m_backgroundBrush.get() : m_alternateBackgroundBrush.get()
			//);
		}

		drawRowCells(row, rowRect.top, scrollOffsetX, scale);
	}
	m_d2dContext->PopAxisAlignedClip();
}

void TableD2DContent::drawRowCells(int row, float rowY, float scrollOffsetX, float scale)
{
	auto& rowData = m_data[row];
	auto currentX = -scrollOffsetX * scale;
	for (size_t column = 0; column < std::size(TableTestData::Columns); ++column)
	{
		auto const rawColumnWidth = m_columnWidthManager.Get(column) * scale;
		auto const& columnData = rowData[column];
		auto const& layoutCache = m_textLayoutCache.GetOrCreate(row, column, columnData);
		if (!m_initialSizing)
		{
			m_d2dContext->DrawTextLayout(
				D2D1::Point2F(currentX, rowY),
				layoutCache,
				m_textBrush.get()
			);
		}
		currentX += rawColumnWidth;
	}
}
