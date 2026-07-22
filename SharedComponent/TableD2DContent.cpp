#include "pch.h"
#include "TableD2DContent.h"
#include "D2DPrimitiveHelper.h"
#include <dxgi1_3.h>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <ranges>
#include <wil/resource.h>
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
	auto const totalHeight = DataCount() * m_tableHeight.ContentRowHeight();
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

std::pair<int, int> TableD2DContent::GetVisibleRowRangeInclusive(float scrollY) const
{
	return GetVisibleRowRangeInclusive(scrollY, m_table_ref.m_tableData.RowCount());
}

std::pair<int, int> TableD2DContent::GetVisibleRowRangeInclusive(float scrollY, int rowCount) const
{
	auto const contentRowHeight = m_tableHeight.ContentRowHeight();
	int const first = (std::max)(0, static_cast<int>(scrollY / contentRowHeight));
	int const last = (std::min)(rowCount - 1, static_cast<int>((scrollY + m_swapChain.CurrentSize.Height) / contentRowHeight));
	return { first, last };
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
	auto const index = m_columnWidthManager.GetColumnIndexFromX(x, -m_scrollOffsetX.load(std::memory_order_relaxed));
	if (index == TableConstants::ResizeColumnIndexNone || !m_table_ref.m_columns->m_data[index]->m_data.m_isResizable)
		return TableConstants::ResizeColumnIndexNone;
	return index;
}

float TableD2DContent::GetViewportHeight() const
{
	return m_swapChain.CurrentSize.Height - m_tableHeight.HeaderRowHeight();
}

float TableD2DContent::GetViewportWidth() const
{
	return m_swapChain.CurrentSize.Width;
}

float TableD2DContent::TotalContentWidth() const
{
	return m_initialSizing.load(std::memory_order_relaxed) ?
		m_swapChain.CurrentSize.Width :
		m_columnWidthManager.SumColumnWidth();
}

void TableD2DContent::DrawPartialCell(int row, int column, std::wstring_view content)
{
	if (!m_swapChain.get())
		return;
	if (m_swapChain.CurrentSize.Width <= 0 || m_swapChain.CurrentSize.Height <= 0)
		return;

	m_textLayoutCache.SetCellContent(row, column, content);

	auto const scale = m_swapChain.Scale;
	auto const scrollOffsetX = m_scrollOffsetX.load(std::memory_order_relaxed);
	auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);
	auto const rawHeaderHeight = m_tableHeight.HeaderRowHeight() * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawHeight = m_swapChain.CurrentSize.Height * scale;
	auto const dataCount = static_cast<int>(m_textLayoutCache.RowCount());
	auto const numColumns = static_cast<int>(m_columnWidthManager.NumColumns());

	auto const& padding = m_resource.m_localTableData.m_contentPadding;
	auto const padLeft = static_cast<float>(padding.Left) * scale;
	auto const padTop  = static_cast<float>(padding.Top)  * scale;

	struct DirtyCell
	{
		int row;
		int column;
		float cellLeft;
		float rowTop;
	};

	//At most 2 entries: the current cell, and the previously partially-drawn cell repainted to sync the other back buffer.
	DirtyCell dirtyCells[2];
	D2D_RECT_F clipRects[2];
	size_t dirtyCount = 0;

	auto addIfVisible = [&](int r, int c)
	{
		if (r < 0 || r >= dataCount || c < 0 || c >= numColumns)
			return;
		if (std::any_of(dirtyCells, dirtyCells + dirtyCount, [r, c](DirtyCell const& d) { return d.row == r && d.column == c; }))
			return;

		auto const rowRect = getRowRect(r, scrollOffsetY, scale);
		auto const cellLeft = m_columnWidthManager.SumColumnWidth(c, -scrollOffsetX) * scale;
		auto const cellRight = cellLeft + m_columnWidthManager.Get(c) * scale;
		auto const clipLeft = (std::max)(cellLeft, 0.f);
		auto const clipRight = (std::min)(cellRight, rawWidth);
		//Inset by 1*scale so the row's top/bottom dividing lines are not cleared.
		auto const clipTop = (std::max)(rowRect.top + 1 * scale, rawHeaderHeight);
		auto const clipBottom = (std::min)(rowRect.bottom - 1 * scale, rawHeight);
		if (clipRight <= clipLeft || clipBottom <= clipTop)
			return;

		dirtyCells[dirtyCount] = { r, c, cellLeft, rowRect.top };
		clipRects[dirtyCount] = { clipLeft, clipTop, clipRight, clipBottom };
		++dirtyCount;
	};

	addIfVisible(row, column);
	addIfVisible(m_lastPartialCellRow, m_lastPartialCellColumn);

	m_lastPartialCellRow = row;
	m_lastPartialCellColumn = column;

	presentClippedRegions(clipRects, dirtyCount, [&](size_t i)
	{
		auto const& dirty = dirtyCells[i];
		if (auto* const bg = getAlternateRowBackgroundBrush(dirty.row))
			m_d2dContext->FillRectangle(clipRects[i], bg);
		if (auto layout = m_textLayoutCache.GetOrCreate(dirty.row, dirty.column))
		{
			m_d2dContext->DrawTextLayout(
				D2D1::Point2F(dirty.cellLeft + padLeft, dirty.rowTop + padTop),
				layout,
				getAlternateRowForegroundBrush(dirty.row)
			);
		}
	});
}

int TableD2DContent::DataCount() const
{
	return m_textLayoutCache.RowCount();
}

void TableD2DContent::SetHover(float y)
{
	int newRow;
	auto const headerHeight = m_tableHeight.HeaderRowHeight();
	if (y <= headerHeight)
		newRow = TableConstants::HoveredRowNone;
	else
	{
		auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);
		newRow = static_cast<int>((y - headerHeight + scrollOffsetY) / m_tableHeight.ContentRowHeight());
	}
	if (std::exchange(m_hoveredRow, newRow) != newRow)
		RequestDraw();
}

D2D_RECT_F TableD2DContent::getRowRect(int row, float scrollOffsetY, float scale) const
{
	auto const rawRowHeight = m_tableHeight.ContentRowHeight() * scale;
	auto const rawHeaderHeight = m_tableHeight.HeaderRowHeight() * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rowTop = rawHeaderHeight + row * rawRowHeight - scrollOffsetY * scale;
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

		bool const canDraw = m_swapChain.get()
			&& m_swapChain.CurrentSize.Width > 0 
			&& m_swapChain.CurrentSize.Height > 0
			&& static_cast<bool>(m_table_ref.m_tableData);
		if (!canDraw)
		{
			//Drop the Draw request but keep queued dirty flags (e.g. AlternateRowDirty) 
			//so nothing is consumed before the table can actually draw.
			auto const rest = m_request.ClearDraw();
			if (rest & FrameRequest::Flag::Stop)
				break;
			m_request.WaitChanged(rest);
			continue;
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
			if (auto newYFloor = static_cast<int>(newY); std::exchange(m_cachedScrollBarY, newYFloor) != newYFloor)
				m_dispatcher.TryEnqueue([this, newY] { m_table_ref.UpdateVerticalScrollBar(newY); });

			m_scrollOffsetY.store(newY, std::memory_order_relaxed);
			drawRequest |= FrameRequest::Flag::FullRedraw;
			if (easedProgress >= 1.0)
				m_isScrolling.store(false, std::memory_order_release);
		}

		if (drawRequest & FrameRequest::Flag::SwapChainDirty)
		{
			m_swapChain.SetTarget(m_d2dContext.get());
			drawRequest |= FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty;
			m_verticalLines.Invalidate();
		}

		if (std::exchange(m_textLayoutCache.Scale, m_swapChain.Scale) != m_swapChain.Scale)
		{
			m_resource.ScaleChanged();
			drawRequest |= FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty;
			m_verticalLines.Invalidate();
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
	if (!m_table_ref.m_tableData)
		return;

	bool fullRedraw = (frame & FrameRequest::Flag::FullRedraw) != 0;
	bool const hoverColorOnly = !fullRedraw && (frame & FrameRequest::Flag::HoverColorDirty);

	if (m_table_ref.m_sharedData.ConsumeChanged())
	{
		auto sharedData = m_table_ref.m_sharedData.GetCopy();
		m_resource.Create(m_d2dContext.get(), std::move(sharedData));
		if (!hoverColorOnly)
		{
			fullRedraw = true;
			//AlternateRowDirty only affects row brushes, not the header bitmap.
			if (!(frame & FrameRequest::Flag::AlternateRowDirty))
				frame |= FrameRequest::Flag::HeaderDirty;
		}
	}

	if (frame & FrameRequest::Flag::VerticalLineDirty)
		m_verticalLines.Invalidate();

	if (frame & FrameRequest::Flag::AlternateRowDirty)
		m_resource.RebuildAlternateRowBrushes(m_d2dContext.get());

	int const hoveredResizeColumn = m_hoveredResizeColumn.load(std::memory_order_relaxed);
	auto const scrollOffsetX = m_scrollOffsetX.load(std::memory_order_relaxed);
	auto const scrollOffsetY = m_scrollOffsetY.load(std::memory_order_relaxed);
	auto const scale = m_swapChain.Scale;

	//SetCellContent indexes m_perColumnCache, so columns must be sized
	//before any RowRequested-driven push reaches the cache.
	m_textLayoutCache.SetNumColumns(m_table_ref.m_columns->m_data.size());

	if (auto const rowCount = static_cast<int>(m_textLayoutCache.RowCount()); rowCount > 0 && m_table_ref.m_tableData)
	{
		//When sorted, a visible display row can map (via m_sortContext.Source) to
		//any source row, so the whole data set must be present in the cache rather
		//than just the visible window.
		auto const [first, last] = m_table_ref.m_sortContext
			? std::pair{ 0, rowCount - 1 }
			: GetVisibleRowRangeInclusive(scrollOffsetY, rowCount);
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
	else if (hoverColorOnly && m_hoveredRow != TableConstants::HoveredRowNone)
		drawPartialHover(m_hoveredRow, m_hoveredRow, scrollOffsetX, scrollOffsetY, scale);
	else if (m_hoveredRow != m_prevHoveredRow)
		drawPartialHover(m_prevHoveredRow, m_hoveredRow, scrollOffsetX, scrollOffsetY, scale);

	m_prevHoveredRow = m_hoveredRow;
}

void TableD2DContent::drawFull(float scrollOffsetX, float scrollOffsetY, int hoveredResizeColumn, int hoveredRow, float scale, bool headerDirty)
{
	auto const rawViewportWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawViewportHeight = m_swapChain.CurrentSize.Height * scale;
	auto const rawRowHeight = m_tableHeight.ContentRowHeight() * scale;
	auto const rawHeaderHeight = m_tableHeight.HeaderRowHeight() * scale;
	m_horizontalLines.Rebuild(rawViewportWidth, rawViewportHeight, rawRowHeight, rawHeaderHeight);

	if (!m_headerBitmap || headerDirty)
		renderHeaderBitmap(hoveredResizeColumn, scrollOffsetX);

	drawVerticalLines();

	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(0, 0));

	drawRows(scrollOffsetX, scrollOffsetY, hoveredRow);
	auto const rawHorizontalStroke = m_resource.m_localTableData.m_horizontalLineThickness * scale;
	auto const rawDataBottomY = rawHeaderHeight + m_textLayoutCache.RowCount() * rawRowHeight - scrollOffsetY * scale;
	m_horizontalLines.Draw(m_d2dContext.get(), scrollOffsetY * scale, rawDataBottomY + rawHorizontalStroke, rawHorizontalStroke);

	if (m_verticalLines)
		m_verticalLines.Draw(m_d2dContext.get(), -scrollOffsetX * scale, rawDataBottomY + rawHorizontalStroke);

	m_d2dContext->DrawBitmap(
		m_headerBitmap.Get(),
		D2D1::RectF(0, 0, rawViewportWidth, rawHeaderHeight),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
	);
	m_d2dContext->EndDraw();

	winrt::check_hresult(m_swapChain->Present(0, 0));
	Frames.fetch_add(1, std::memory_order_relaxed);

	if (m_initialSizing && m_textLayoutCache.RowCount() > 0)
	{
		auto const& columns = m_table_ref.m_columns->m_data;
		m_columnWidthManager.InitializeColumnWidth(m_swapChain.CurrentSize.Width, m_swapChain.Scale, columns);

		//column HorizontalAlignment are initialized only once
		for (size_t column = 0; column < columns.size(); ++column)
		{
			auto const columnHA = D2DConvert::ToDWriteHorizontalAlignment(columns[column]->HorizontalAlignment());
			m_textLayoutCache.SetColumnFormat(column, columnHA, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		}

		m_initialSizing = false;
		//Column widths just got resolved — header layout depends on them.
		RequestDraw(FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty);
		m_dispatcher.TryEnqueue([this, scrollOffsetX] {
			m_table_ref.UpdateHorizontalScrollBar(scrollOffsetX);
			m_table_ref.m_overlayManager.OnColumnsInitialized();
		});
	}
}

void TableD2DContent::renderHeaderBitmap(int hoveredResizeColumn, float scrollOffsetX)
{
	auto const scale = m_swapChain.Scale;
	auto const widthPx  = static_cast<unsigned>(std::ceil(m_swapChain.CurrentSize.Width * scale));
	auto const heightPx = static_cast<unsigned>(std::ceil(m_tableHeight.HeaderRowHeight() * scale));

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
	auto const rawHeaderHeight = m_tableHeight.HeaderRowHeight() * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const rawHeight = m_swapChain.CurrentSize.Height * scale;
	auto const rawCornerRadius = TableConstants::CornerRadius * scale;
	auto const dataCount = m_textLayoutCache.RowCount();

	struct DirtyRow
	{
		int row;
		D2D_RECT_F rowRect; //unclipped — drives rounded fill and text origin
	};

	//Up to 4 entries: this frame's (old, new) plus the previous partial frame's (old, new) repainted to sync the other back buffer.
	DirtyRow dirtyRows[4];
	D2D_RECT_F clipRects[4];
	size_t dirtyCount = 0;

	auto addIfVisible = [&](int row)
	{
		if (row == TableConstants::HoveredRowNone || row < 0 || row >= dataCount)
			return;
		if (std::any_of(dirtyRows, dirtyRows + dirtyCount, [row](DirtyRow const& d) { return d.row == row; }))
			return;
		auto const rowRect = getRowRect(row, scrollOffsetY, scale);
		auto const clipTop = (std::max)(rowRect.top + 1 * scale, rawHeaderHeight);
		auto const clipBottom = (std::min)(rowRect.bottom - 1 * scale, rawHeight);
		if (clipBottom <= clipTop)
			return;
		dirtyRows[dirtyCount] = { row, rowRect };
		clipRects[dirtyCount] = { 0, clipTop, rawWidth, clipBottom };
		++dirtyCount;
	};
	addIfVisible(oldRow);
	addIfVisible(newRow);
	addIfVisible(m_lastPartialOldRow);
	addIfVisible(m_lastPartialNewRow);

	m_lastPartialOldRow = oldRow;
	m_lastPartialNewRow = newRow;

	presentClippedRegions(clipRects, dirtyCount, [&](size_t i)
	{
		auto const& dirty = dirtyRows[i];
		fillAlternateRowBackground(dirty.row, dirty.rowRect);
		if (dirty.row == newRow && m_resource.m_hoverBrush)
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
		if (m_verticalLines)
			m_verticalLines.Draw(m_d2dContext.get(), -scrollOffsetX * scale, clipRects[i].top, clipRects[i].bottom);
	});
}

void TableD2DContent::drawHeader(int hoveredResizeColumn, float scrollOffsetX)
{
	auto const scale = m_swapChain.Scale;
	auto currentX = -scrollOffsetX * scale;
	auto rawHeaderHeight = m_tableHeight.HeaderRowHeight() * scale;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto const& localData = m_resource.m_localTableData;
	auto const& padding = localData.m_contentPadding;
	auto const padLeft   = static_cast<float>(padding.Left)   * scale;
	auto const padTop    = static_cast<float>(padding.Top)    * scale;
	auto const padRight  = static_cast<float>(padding.Right)  * scale;
	auto const padBottom = static_cast<float>(padding.Bottom) * scale;
	auto const verticalLineSpace = localData.m_verticalLineColor.a > 0.f ? localData.m_verticalLineThickness * scale : 0.f;
	auto const paddedMaxHeight = (std::max)(0.f, rawHeaderHeight - padTop - padBottom);
	
	if (m_resource.m_headerBackgroundBrush)
		m_d2dContext->FillRectangle(D2D1::RectF(0, 0, rawWidth, rawHeaderHeight), m_resource.m_headerBackgroundBrush.get());

	auto const& columns = m_table_ref.m_columns->m_data;

	for (size_t column = 0; column < columns.size(); ++column)
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
				: (std::max)(0.f, rawColumnWidth - verticalLineSpace - padLeft - padRight);
			auto const layoutMaxHeight = m_initialSizing
				? rawHeaderHeight
				: paddedMaxHeight;

			if (auto const* stringContent = std::get_if<winrt::hstring>(&columns[column]->m_data.m_content))
			{
				auto const horizontalAlignment = D2DConvert::ToDWriteHorizontalAlignment(columns[column]->HorizontalAlignment());
				auto layout = m_textLayoutCache.GetOrCreate(
					column,
					*stringContent,
					layoutMaxWidth, layoutMaxHeight,
					horizontalAlignment,
					m_table_ref.m_tableProperty.HeaderVerticalAlignment
				);

				if (!m_initialSizing)
					m_d2dContext->DrawTextLayout({ currentX + verticalLineSpace + padLeft, padTop }, layout, m_resource.m_headerTextBrush.get());
			}

			if (m_table_ref.m_sortContext.sortParameter.sortColumn == static_cast<int>(column))
			{
				//draw sort indicator here
			}
		}
		currentX += rawColumnWidth;
	}
}

void TableD2DContent::drawRows(float scrollOffsetX, float scrollOffsetY, int hoveredRow)
{
	auto const scale = m_swapChain.Scale;
	auto const rawBottom = m_swapChain.CurrentSize.Height * scale;
	auto const rawRight = m_swapChain.CurrentSize.Width * scale;
	m_d2dContext->PushAxisAlignedClip(D2D1::RectF(0, m_tableHeight.HeaderRowHeight() * scale, rawRight, rawBottom), D2D1_ANTIALIAS_MODE_ALIASED);

	auto rawCornerRadius = TableConstants::CornerRadius * scale;

	auto [first, last] = GetVisibleRowRangeInclusive(scrollOffsetY);
	for (int row = first; row <= last; ++row)
	{
		auto const rowRect = getRowRect(row, scrollOffsetY, scale);

		fillAlternateRowBackground(row, rowRect);

		if (row == hoveredRow && m_resource.m_hoverBrush)
		{
			D2D1_ROUNDED_RECT const fill
			{
				.rect = D2D1::RectF(rowRect.left, rowRect.top + 1, rowRect.right, rowRect.bottom - 1),
				.radiusX = rawCornerRadius,
				.radiusY = rawCornerRadius
			};
			m_d2dContext->FillRoundedRectangle(&fill, m_resource.m_hoverBrush.get());
		}

		drawRowCells(row, rowRect.top, scrollOffsetX, scale);
	}
	m_d2dContext->PopAxisAlignedClip();
}

void TableD2DContent::drawRowCells(int row, float rowY, float scrollOffsetX, float scale)
{
	auto const& localData = m_resource.m_localTableData;
	auto const& padding = localData.m_contentPadding;
	auto const padLeft = static_cast<float>(padding.Left) * scale;
	auto const padTop  = static_cast<float>(padding.Top)  * scale;
	auto const verticalLineSpace = localData.m_verticalLineColor.a > 0.f ? localData.m_verticalLineThickness * scale : 0.f;
	auto const rawWidth = m_swapChain.CurrentSize.Width * scale;
	auto currentX = -scrollOffsetX * scale;
	auto* const textBrush = getAlternateRowForegroundBrush(row);
	for (size_t column = 0; column < m_table_ref.m_columns->m_data.size(); ++column)
	{
		auto const rawColumnWidth = m_initialSizing? (std::numeric_limits<float>::max)() : m_columnWidthManager.Get(column) * scale;
		if (currentX + rawColumnWidth > 0 || m_initialSizing)
		{
			if (currentX >= rawWidth && !m_initialSizing) //all later columns are off-screen-right
				return;

			//Render the cell of the source row this display row maps to when sorted.
			auto const layoutCache = m_textLayoutCache.GetOrCreate(m_table_ref.m_sortContext.Source(row), column);
			if (!m_initialSizing && layoutCache)
			{
				m_d2dContext->DrawTextLayout(
					D2D1::Point2F(currentX + verticalLineSpace + padLeft, rowY + padTop),
					layoutCache,
					textBrush
				);
			}
		}
		currentX += rawColumnWidth;
	}
}

void TableD2DContent::fillAlternateRowBackground(int row, D2D_RECT_F const& rowRect)
{
	if (auto* const bg = getAlternateRowBackgroundBrush(row))
		m_d2dContext->FillRectangle(rowRect, bg);
}

ID2D1SolidColorBrush* TableD2DContent::getAlternateRowBackgroundBrush(int row) const
{
	auto const& brushes = m_resource.m_alternateRowBrushes;
	if (brushes.empty())
		return nullptr;
	return brushes[row % brushes.size()].m_background.get();
}

ID2D1SolidColorBrush* TableD2DContent::getAlternateRowForegroundBrush(int row) const
{
	auto const& brushes = m_resource.m_alternateRowBrushes;
	if (!brushes.empty())
	{
		if (auto* const fg = brushes[row % brushes.size()].m_foreground.get())
			return fg;
	}
	return m_resource.m_contentTextBrush.get();
}

void TableD2DContent::drawVerticalLines()
{
	if (!m_resource.m_verticalLineBrush)
		return;

	auto const numColumns = m_table_ref.m_columns->m_data.size();
	if (numColumns == 0 || m_initialSizing.load(std::memory_order_relaxed))
		return;

	auto const scale = m_swapChain.Scale;
	auto const rawWidth  = static_cast<UINT32>(std::ceil(m_columnWidthManager.SumColumnWidth() * scale));
	auto const rawHeight = static_cast<UINT32>(std::ceil(m_swapChain.CurrentSize.Height * scale));
	if (rawWidth == 0 || rawHeight == 0)
		return;

	auto const widthVersion = m_columnWidthManager.Version();
	if (!m_verticalLines.CompareVersion(widthVersion))
		return;

	auto target = m_verticalLines.RecreateIfNeeded(m_d2dContext.get(), rawWidth, rawHeight);

	winrt::com_ptr<ID2D1Image> previousTarget;
	auto restoreTarget = wil::scope_exit([&] { m_d2dContext->SetTarget(previousTarget.get()); });
	m_d2dContext->GetTarget(previousTarget.put());
	m_d2dContext->SetTarget(target);

	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(0, 0));

	auto const lineLength = static_cast<float>(rawHeight);
	auto const strokeWidth = m_resource.m_localTableData.m_verticalLineThickness * scale;
	auto brush = m_resource.m_verticalLineBrush.get();


	//Skip i = 0 and i = numColumns: those are the table's outer left/right edges
	//and are now drawn by the parent control's BorderBrush/BorderThickness.
	for (size_t i = 1; i < numColumns; ++i)
	{
		D2DPrimitiveHelper::DrawVerticalLine(
			m_d2dContext.get(),
			m_columnWidthManager.SumColumnWidth(i, 0) * scale,
			0,
			lineLength,
			brush,
			strokeWidth
		);
	}

	winrt::check_hresult(m_d2dContext->EndDraw());
}
