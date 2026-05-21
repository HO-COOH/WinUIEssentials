#include "pch.h"
#include "TableD2DContent.h"
#include "D2DPrimitiveHelper.h"
#include <dxgi1_3.h>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <ranges>
#include "Table.h"
#include "Easing.hpp"
#include "RowRequestedEventArgs.h"

TableD2DContent::TableD2DContent(winrt::PackageRoot::implementation::Table& table) : 
	m_dispatcher{ table },
	m_table_ref{ table }, 
	m_drawThread{ [this] { try { drawThreadProc(); } catch (winrt::hresult const&) {} } }
{
	m_swapChain.Set(m_d3dDevice.get(), table);

	auto d2d1Device = DirectN::GetD2D1Device(d2d1Factory.get(), m_d3dDevice.get());
	winrt::check_hresult(d2d1Device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, m_d2dContext.put()));
}

TableD2DContent::~TableD2DContent()
{
	Stop();
}

void TableD2DContent::Stop()
{
	if (!m_drawThread.joinable())
		return;
	RequestDraw(FrameRequest::Flag::Stop);
	m_drawThread.join();
}

void TableD2DContent::DetachSwapChain(winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& panel)
{
	m_swapChain.DetachFromPanel(panel);
}

void TableD2DContent::RequestDraw(FrameRequest::Flags extra)
{
	m_request.Set(static_cast<FrameRequest::Flags>(FrameRequest::Flag::Draw) | extra);
	m_request.WakeOne();
}

void TableD2DContent::SizeChanged(
	winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender,
	winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e)
{
	if (!m_swapChain.SizeChanged(sender, e))
		return;
	updateScrollOffsets();
	RequestDraw(FrameRequest::Flag::SwapChainDirty | FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty);
}

void TableD2DContent::updateScrollOffsets()
{
	auto const totalHeight = DataCount() * TableConstants::RowHeight;
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
	RequestDraw(FrameRequest::Flag::SwapChainDirty | FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty);
}

void TableD2DContent::SetScrollOffsetX(float x)
{
	m_scrollOffsetX.store(x, std::memory_order_relaxed);
	//Header scrolls with horizontal offset.
	m_request.Set(FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty);
}

void TableD2DContent::SetScrollOffsetY(float y)
{
	m_scrollOffsetY.store(y, std::memory_order_relaxed);
	m_request.Set(FrameRequest::Flag::FullRedraw);
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
	m_pendingScrollRequest.Set(ScrollOffsetY(), targetY);
	RequestDraw(FrameRequest::Flag::FullRedraw);
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
	return m_pendingScrollRequest.GetTarget();
}

int TableD2DContent::HoveredResizeColumn() const
{
	return m_hoveredResizeColumn.load(std::memory_order_relaxed);
}

bool TableD2DContent::SetHoveredResizeColumn(int index)
{
	bool const changed = m_hoveredResizeColumn.exchange(index, std::memory_order_relaxed) != index;
	if (changed)
	{
		//Resize-handle hover lives in the header row.
		m_request.Set(FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty);
	}
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
	return m_initialSizing.load(std::memory_order_relaxed) ?
		m_swapChain.CurrentSize.Width :
		m_columnWidthManager.SumColumnWidth(m_table_ref.m_columns->m_data.size());
}

int TableD2DContent::DataCount() const
{
	return m_textLayoutCache.RowCount();
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
	while (true)
	{
		if (!m_isScrolling.load(std::memory_order_acquire))
		{
			m_request.WaitForDraw();
		}

		auto drawRequest = m_request.ClearAll();
		if (drawRequest & FrameRequest::Flag::Stop)
			break;

		//pick up a new scroll request if one arrived.
		//acquire: pairs with release store in StartSmoothScrollY so the
		//field writes there are visible here.
		if (m_pendingScrollRequest.isPending.exchange(false, std::memory_order_acquire))
		{
			m_activeScrollRequest.Set(m_pendingScrollRequest);
			m_isScrolling.store(true, std::memory_order_release);
		}

		//advance the scroll animation for this frame
		if (m_isScrolling.load(std::memory_order_acquire))
		{
			auto const progress = m_activeScrollRequest.Progress();
			auto const easedProgress = EasedProgress(progress, 5);
			auto const newY = m_activeScrollRequest.EasedValue(easedProgress);

			//only call dispatcher when the scrollBar position actually changed
			if (auto const newYFloor = static_cast<int>(newY); newYFloor != m_cachedScrollBarY)
			{
				m_dispatcher.TryEnqueue([this, newY] { m_table_ref.updateVerticalScrollBar(newY); });
				m_cachedScrollBarY = newYFloor;
			}

			m_scrollOffsetY.store(newY, std::memory_order_relaxed);
			drawRequest |= FrameRequest::Flag::FullRedraw;
			if (easedProgress >= 1.0)
				m_isScrolling.store(false, std::memory_order_release);
		}

		if (drawRequest & FrameRequest::Flag::SwapChainDirty)
		{
			m_swapChain.SetTarget(m_d2dContext.get());
			drawRequest |= FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty;
		}

		if (std::exchange(m_textLayoutCache.Scale, m_swapChain.Scale) != m_swapChain.Scale)
		{
			m_resource.ScaleChanged();
			drawRequest |= FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty;
		}

		draw(drawRequest);
#if defined Build_UWPPackage
		m_swapChain.WaitForVBlank();
#endif
	}
}

void TableD2DContent::draw(FrameRequest::Flags frame)
{
	if (!m_swapChain.get())
		return;
	if (m_swapChain.CurrentSize.Width <= 0 || m_swapChain.CurrentSize.Height <= 0)
		return;

	bool fullRedraw = (frame & FrameRequest::Flag::FullRedraw) != 0;

	if (m_table_ref.m_sharedData.ConsumeChanged())
	{
		auto sharedData = m_table_ref.m_sharedData.GetCopy();
		m_resource.Create(m_d2dContext.get(), std::move(sharedData));
		fullRedraw = true;
		frame |= FrameRequest::Flag::HeaderDirty;
	}

	int const hoveredResizeColumn = m_hoveredResizeColumn.load(std::memory_order_relaxed);
	auto const scrollOffsetX = m_scrollOffsetX.load(std::memory_order_relaxed);
	auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);
	auto const scale = m_swapChain.Scale;

	//SetCellContent indexes m_perColumnCache, so columns must be sized
	//before any RowRequested-driven push reaches the cache.
	m_textLayoutCache.SetNumColumns(m_table_ref.m_columns->m_data.size());

	if (auto const rowCount = static_cast<int>(m_textLayoutCache.RowCount()); rowCount > 0 && m_table_ref.m_tableData)
	{
		auto const rawRowHeight = TableConstants::RowHeight * scale;
		auto const rawBottom = m_swapChain.CurrentSize.Height * scale;
		auto const rawScrollOffsetY = scrollOffsetY * scale;
		int const first = (std::max)(0, static_cast<int>(rawScrollOffsetY / rawRowHeight));
		int const last  = (std::min)(rowCount - 1, static_cast<int>((rawScrollOffsetY + rawBottom) / rawRowHeight));

		if (std::ranges::any_of(std::ranges::iota_view{ first, last + 1 }, [this](int r) { return m_textLayoutCache.IsRowStale(r); }))
		{
			//Draw-thread call. ITableData implementations must be free-threaded
			//or marshal internally; documented on the IDL.
			auto args = winrt::make_self<winrt::PackageRoot::implementation::RowRequestedEventArgs>(first, last, m_table_ref);
			m_table_ref.m_tableData.RowRequested(*args);
			fullRedraw = true;
		}
	}

	if (fullRedraw)
	{
		bool const headerDirty = (frame & FrameRequest::Flag::HeaderDirty) != 0;
		drawFull(scrollOffsetX, scrollOffsetY, hoveredResizeColumn, m_hoveredRow, scale, headerDirty);
	}
	else if (m_hoveredRow != m_prevHoveredRow)
		drawPartialHover(m_prevHoveredRow, m_hoveredRow, scrollOffsetX, scrollOffsetY, scale);

	m_prevHoveredRow = m_hoveredRow;
}

void TableD2DContent::drawFull(float scrollOffsetX, float scrollOffsetY, int hoveredResizeColumn, int hoveredRow, float scale, bool headerDirty)
{
	auto const rawViewportWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawViewportHeight = m_swapChain.CurrentSize.Height * scale;
	auto const rawRowHeight = TableConstants::RowHeight * scale;
	auto const rawHeaderHeight = TableConstants::HeaderHeight * scale;
	m_tableLines.Rebuild(rawViewportWidth, rawViewportHeight, rawRowHeight, rawHeaderHeight);

	if (!m_headerBitmap || headerDirty)
		renderHeaderBitmap(hoveredResizeColumn, scrollOffsetX);

	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(0, 0));

	drawRows(scrollOffsetX, scrollOffsetY, hoveredRow);
	auto const rawDataBottomY = rawHeaderHeight + m_textLayoutCache.RowCount() * rawRowHeight - scrollOffsetY * scale;
	m_tableLines.Draw(m_d2dContext.get(), scrollOffsetY * scale, rawDataBottomY - 1);

	m_d2dContext->DrawBitmap(
		m_headerBitmap.Get(),
		D2D1::RectF(0, 0, rawViewportWidth, rawHeaderHeight),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	);
	m_d2dContext->EndDraw();

	DXGI_PRESENT_PARAMETERS presentParameters{};
	winrt::check_hresult(m_swapChain->Present1(0, 0, &presentParameters));
	Frames.fetch_add(1, std::memory_order_relaxed);

	if (m_initialSizing && m_textLayoutCache.RowCount() > 0)
	{
		m_columnWidthManager.GetInitialColumnWidth(m_swapChain.CurrentSize.Width, m_swapChain.Scale);
		m_initialSizing = false;
		//Column widths just got resolved — header layout depends on them.
		RequestDraw(FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty);
	}
}

void TableD2DContent::renderHeaderBitmap(int hoveredResizeColumn, float scrollOffsetX)
{
	auto const scale = m_swapChain.Scale;
	auto const widthPx  = static_cast<unsigned>(std::ceil(m_swapChain.CurrentSize.Width * scale));
	auto const heightPx = static_cast<unsigned>(std::ceil(TableConstants::HeaderHeight * scale));

	auto target = m_headerBitmap.RecreateIfNeeded(m_d2dContext.get(), widthPx, heightPx);

	winrt::com_ptr<ID2D1Image> prevTarget;
	m_d2dContext->GetTarget(prevTarget.put());
	m_d2dContext->SetTarget(target);
	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(0, 0));
	drawHeader(hoveredResizeColumn, scrollOffsetX);
	winrt::check_hresult(m_d2dContext->EndDraw());
	m_d2dContext->SetTarget(prevTarget.get());
}

void TableD2DContent::drawPartialHover(int oldRow, int newRow, float scrollOffsetX, float scrollOffsetY, float scale)
{
	auto const rawRowHeight = TableConstants::RowHeight * scale;
	auto const rawHeaderHeight = TableConstants::HeaderHeight * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawHeight = m_swapChain.CurrentSize.Height * scale;
	auto const rawScrollY = scrollOffsetY * scale;
	auto const rawCornerRadius = TableConstants::CornerRadius * scale;
	auto const dataCount = m_textLayoutCache.RowCount();

	struct DirtyRow
	{
		int row;
		D2D_RECT_F rowRect;   //unclipped — drives rounded fill and text origin
		float clipTop;        //clipped-and-inset viewport region we actually write
		float clipBottom;
	};

	//Up to 4 entries: this frame's (old, new) plus the previous partial frame's (old, new) repainted to sync the other back buffer.
	DirtyRow dirtyRows[4];
	int dirtyCount = 0;

	auto addIfVisible = [&](int row)
	{
		if (row == TableConstants::HoveredRowNone || row < 0 || row >= dataCount)
			return;
		for (int i = 0; i < dirtyCount; ++i)
			if (dirtyRows[i].row == row)
				return;
		auto const rowRect = getRowRect(row, scrollOffsetY, scale);
		auto const clipTop = (std::max)(rowRect.top + 1 * scale, rawHeaderHeight);
		auto const clipBottom = (std::min)(rowRect.bottom - 1 * scale, rawHeight);
		if (clipBottom <= clipTop)
			return;
		dirtyRows[dirtyCount++] = { row, rowRect, clipTop, clipBottom };
	};
	addIfVisible(oldRow);
	addIfVisible(newRow);
	addIfVisible(m_lastPartialOldRow);
	addIfVisible(m_lastPartialNewRow);

	m_lastPartialOldRow = oldRow;
	m_lastPartialNewRow = newRow;

	if (dirtyCount == 0)
		return;

	m_d2dContext->BeginDraw();
	for (int i = 0; i < dirtyCount; ++i)
	{
		auto const& dirty = dirtyRows[i];
		m_d2dContext->PushAxisAlignedClip(
			D2D1::RectF(0, dirty.clipTop, rawWidth, dirty.clipBottom),
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
			m_d2dContext->FillRoundedRectangle(&fill, m_resource.m_hoverBrush.get());
		}

		drawRowCells(dirty.row, dirty.rowRect.top, scrollOffsetX, scale);
		m_d2dContext->PopAxisAlignedClip();
	}
	m_d2dContext->EndDraw();

	RECT rects[4];
	for (int i = 0; i < dirtyCount; ++i)
	{
		auto const& dirty = dirtyRows[i];
		rects[i] = RECT{
			.left = 0,
			.top = static_cast<LONG>(std::floor(dirty.clipTop)),
			.right = static_cast<LONG>(std::ceil(rawWidth)),
			.bottom = static_cast<LONG>(std::ceil(dirty.clipBottom))
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
	auto const& padding = m_resource.m_localTableData.m_contentPadding;
	auto const padLeft   = static_cast<float>(padding.Left)   * scale;
	auto const padTop    = static_cast<float>(padding.Top)    * scale;
	auto const padRight  = static_cast<float>(padding.Right)  * scale;
	auto const padBottom = static_cast<float>(padding.Bottom) * scale;
	auto const paddedMaxHeight = (std::max)(0.f, rawHeaderHeight - padTop - padBottom);
	
	if (m_resource.m_headerBackgroundBrush)
		m_d2dContext->FillRectangle(D2D1::RectF(0, 0, rawWidth, rawHeaderHeight), m_resource.m_headerBackgroundBrush.get());

	for (size_t column = 0; column < m_table_ref.m_columns->m_data.size(); ++column)
	{
		auto const rawColumnWidth = m_initialSizing? (std::numeric_limits<float>::max)() : m_columnWidthManager.Get(column) * scale;
		if (currentX + rawColumnWidth > 0 || m_initialSizing)
		{
			if (currentX >= rawWidth && !m_initialSizing) //early return only if not initialize sizing
				return;

			//Pass padded bounds into the cache so it only calls SetMax*
			//when the value actually differs from what it last stored.
			//Initial-sizing keeps the unclamped width (max-float) so the
			//natural-width measurement in ColumnWidthManager is unaffected.
			auto const layoutMaxWidth  = m_initialSizing
				? rawColumnWidth
				: (std::max)(0.f, rawColumnWidth - padLeft - padRight);
			auto const layoutMaxHeight = m_initialSizing
				? rawHeaderHeight
				: paddedMaxHeight;

			auto layout = m_textLayoutCache.GetOrCreate(
				column,
				m_table_ref.m_columns->m_data[column]->m_data.m_stringContent,
				layoutMaxWidth, layoutMaxHeight,
				m_table_ref.m_data.HeaderHorizontalAlignment,
				m_table_ref.m_data.HeaderVerticalAlignment
			);

			if (!m_initialSizing)
				m_d2dContext->DrawTextLayout({ currentX + padLeft, padTop }, layout, m_resource.m_headerTextBrush.get());

			if (m_sortColumnIndex == static_cast<int>(column))
			{
				//draw sort indicator here
			}


			if (column != (m_table_ref.m_columns->m_data.size() - 1))
			{
				//the resize handle do not needs to be drawn for the last column
				D2DPrimitiveHelper::DrawVerticalLine(
					m_d2dContext.get(),
					currentX + rawColumnWidth - 1,
					TableConstants::PillPaddingY * scale,
					(TableConstants::RowHeight - TableConstants::PillPaddingY) * scale,
					hoveredResizeColumn == column ? m_resource.m_pillBrush.get() : m_resource.m_headerTextBrush.get()
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
	int const last = (std::min<int>)(DataCount() - 1, static_cast<int>((rawScrollOffsetY + rawBottom) / rawRowHeight));

	auto rawCornerRadius = TableConstants::CornerRadius * scale;

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
			m_d2dContext->FillRoundedRectangle(&fill, m_resource.m_hoverBrush.get());
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
	auto const& padding = m_resource.m_localTableData.m_contentPadding;
	auto const padLeft = static_cast<float>(padding.Left) * scale;
	auto const padTop  = static_cast<float>(padding.Top)  * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto currentX = -scrollOffsetX * scale;
	for (size_t column = 0; column < m_table_ref.m_columns->m_data.size(); ++column)
	{
		auto const rawColumnWidth = m_initialSizing? (std::numeric_limits<float>::max)() : m_columnWidthManager.Get(column) * scale;
		if (currentX + rawColumnWidth > 0 || m_initialSizing)
		{
			if (currentX >= rawWidth && !m_initialSizing) //all later columns are off-screen-right
				return;

			auto const layoutCache = m_textLayoutCache.GetOrCreate(row, column);
			if (!m_initialSizing && layoutCache)
			{
				//maxWidth/maxHeight already reflect padding — pushed into the
				//layout cache by ColumnWidthManager when column widths change.
				//Here we only offset the draw origin by the left/top inset.
				m_d2dContext->DrawTextLayout(
					D2D1::Point2F(currentX + padLeft, rowY + padTop),
					layoutCache,
					m_resource.m_contentTextBrush.get()
				);
			}
		}
		currentX += rawColumnWidth;
	}
}
