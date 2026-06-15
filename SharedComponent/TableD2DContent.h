#pragma once
#include <winrt/base.h>
#include "DispatcherAdapter.h"
#include <d2d1_1.h>
#include <d3d11.h>
#include <dwrite_3.h>
#include <atomic>
#include <thread>
#include <vector>
#include "D2DConvert.hpp"
#include "SwapChainInterop.h"
#include "TextLayoutCache.h"
#include "TableConstants.hpp"
#include "ScrollRequest.h"
#include "DirectN.h"
#include "ColumnWidthManager.h"
#include "TableHorizontalLines.h"
#include "TableD2DResource.h"
#include "FrameRequest.h"
#include "TableHeaderBitmap.h"
#include "TableVerticalLines.h"
#include "TableHeightManager.h"

namespace winrt
{
	namespace PackageRoot::implementation
	{
		struct Table;
	}

	namespace Microsoft::UI::Xaml
	{
		namespace Controls
		{
			struct SwapChainPanel;
		}

		struct SizeChangedEventArgs;
	}
}


class TableD2DContent
{
public:
	DispatcherAdapter m_dispatcher;

	TableD2DContent(winrt::PackageRoot::implementation::Table& table);
	~TableD2DContent();

	TableD2DContent(TableD2DContent const&) = delete;
	TableD2DContent& operator=(TableD2DContent const&) = delete;

	void Stop();
	void DetachSwapChain(winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& panel);

	void RequestDraw(FrameRequest::Flags extra = 0);
	void RequestDraw(FrameRequest::Flag extra) { RequestDraw(static_cast<FrameRequest::Flags>(extra)); }

	// UI-thread only: forward the SwapChainPanel size-changed event.
	void SizeChanged(
		winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender,
		winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e);

	// UI-thread only: forward the SwapChainPanel composition-scale-changed
	// event. Fires when the window moves to a monitor with a different DPI.
	void CompositionScaleChanged(winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender);

	void SetScrollOffsetX(float x);
	void SetScrollOffsetY(float y);
	float ScrollOffsetX() const;
	float ScrollOffsetY() const;
	std::pair<int, int> GetVisibleRowRangeInclusive(float scrollY) const;
	std::pair<int, int> GetVisibleRowRangeInclusive(float scrollY, int rowCount) const;

	void StartSmoothScrollY(float targetY);
	void StopSmoothScroll();
	bool IsScrolling() const;
	float SmoothScrollTargetY() const;

	[[nodiscard]] bool SetHoveredResizeColumn(int index); //return whether hovered column change

	int GetResizeColumnIndex(float x) const;

	float GetViewportWidth() const;
	float GetViewportHeight() const;
	float TotalContentWidth() const;

	//When doing an edit
	void DrawPartialCell(int row, int column, std::wstring_view content);

	int DataCount() const;
	void SetHover(float y);
	std::atomic_int Frames{ 0 };
private:
	void drawThreadProc();
	void draw(FrameRequest::Flags frame);
	void drawFull(float scrollOffsetX, float scrollOffsetY, int hoveredResizeColumn, int hoveredRow, float scale, bool headerDirty);
	void drawPartialHover(int oldRow, int newRow, float scrollOffsetX, float scrollOffsetY, float scale);

	template<size_t N>
	void presentClippedRegions(D2D_RECT_F const (&clipRects)[N], size_t count, auto&& drawAt)
	{
		if (count == 0)
			return;

		m_d2dContext->BeginDraw();
		for (size_t i = 0; i < count; ++i)
		{
			m_d2dContext->PushAxisAlignedClip(clipRects[i], D2D1_ANTIALIAS_MODE_ALIASED);
			m_d2dContext->Clear(D2D1::ColorF(0, 0));
			drawAt(i);
			m_d2dContext->PopAxisAlignedClip();
		}
		m_d2dContext->EndDraw();

		RECT rects[N];
		std::transform(clipRects, clipRects + count, rects, D2DConvert::ToRect);

		DXGI_PRESENT_PARAMETERS const params
		{
			.DirtyRectsCount = static_cast<UINT>(count),
			.pDirtyRects = rects
		};
		winrt::check_hresult(m_swapChain->Present1(0, 0, &params));
		Frames.fetch_add(1, std::memory_order_relaxed);
	}

	void drawHeader(int hoveredResizeColumn, float scrollOffsetX);
	//Renders the header into m_headerBitmap; called only when header state
	//changed (column widths, horizontal scroll, hovered resize column, scale,
	//viewport width, shared data, initial sizing). Scroll frames blit this
	//bitmap instead of re-running the per-column text + line pass.
	void renderHeaderBitmap(int hoveredResizeColumn, float scrollOffsetX);
	void drawRows(float scrollOffsetX, float scrollOffsetY, int hoveredRow);
	void drawRowCells(int row, float rowY, float scrollOffsetX, float scale);
	void drawVerticalLines();
	void updateScrollOffsets();
	D2D_RECT_F getRowRect(int row, float scrollOffsetY, float scale) const;

	winrt::com_ptr<ID2D1Factory1> d2d1Factory = DirectN::CreateD2D1Factory();
	winrt::com_ptr<ID3D11Device> m_d3dDevice = DirectN::CreateD3D11Device();
	winrt::com_ptr<ID2D1DeviceContext> m_d2dContext;
	winrt::com_ptr<IDWriteFactory6> m_dwriteFactory = DirectN::CreateDWriteFactory<IDWriteFactory6>();
	SwapChainInterop m_swapChain;

public:
	TableHeightManager m_tableHeight{ m_dwriteFactory.get() };
	TextLayoutCache m_textLayoutCache{ m_dwriteFactory.get() };
	ColumnWidthManager m_columnWidthManager{ m_textLayoutCache, m_resource.m_localTableData, m_tableHeight };
private:
	TableD2DResource m_resource{ m_textLayoutCache };
	TableHorizontalLines m_horizontalLines{ d2d1Factory.get(), m_resource };
	TableVerticalLines m_verticalLines;
	std::atomic<float> m_scrollOffsetX{ 0.f };
	std::atomic<float> m_scrollOffsetY{ 0.f };
	int m_hoveredRow{ TableConstants::HoveredRowNone };
	std::atomic<bool> m_initialSizing{ true };
	std::atomic<bool> m_isScrolling{ false };

	//All per-frame draw-thread signals (Draw, FullRedraw, HeaderDirty,
	//SwapChainDirty, Stop) packed into one atomic word. Initial state requests
	//the first frame to do a full redraw and build the header cache.
	FrameRequest m_request{ FrameRequest::Flag::FullRedraw | FrameRequest::Flag::HeaderDirty };

	std::atomic<int> m_hoveredResizeColumn{ TableConstants::ResizeColumnIndexNone };
	int m_sortColumnIndex = -1;

	int m_prevHoveredRow{ TableConstants::HoveredRowNone };

	//These are for clearing up the back buffers because BufferCount = 2]
	//We need to explicitly redrawing the hovered row with the previous buffer
	int m_lastPartialOldRow{ TableConstants::HoveredRowNone };
	int m_lastPartialNewRow{ TableConstants::HoveredRowNone };

	//Same back-buffer-staleness compensation as the hover pair, but for the
	//single cell most recently repainted by DrawPartialCell.
	int m_lastPartialCellRow{ -1 };
	int m_lastPartialCellColumn{ -1 };

	//Draw-thread-only. Floor of the last scroll offset for which the
	//scrollbar-thumb update was dispatched to the UI thread. Gates
	//sub-pixel-equivalent redundant hops during smooth-scroll animation.
	//Sentinel ensures the first frame dispatches.
	int m_cachedScrollBarY{ -1 };

	ScrollRequest m_pendingScrollRequest;
	ScrollRequest m_activeScrollRequest;

	TableHeaderBitmap m_headerBitmap;

	winrt::PackageRoot::implementation::Table& m_table_ref;

	std::thread m_drawThread;
};
