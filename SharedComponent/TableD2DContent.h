#pragma once
#include <winrt/base.h>
#include "DispatcherAdapter.h"
#include <d2d1_1.h>
#include <d3d11.h>
#include <dwrite.h>
#include <atomic>
#include <thread>
#include <vector>
#include "SwapChainInterop.h"
#include "TextLayoutCache.h"
#include "TableTestData.hpp"
#include "TableConstants.hpp"
#include "ScrollRequest.h"
#include "DirectN.h"
#include "ColumnWidthManager.h"
#include "TableLinesCache.h"
#include "TableD2DResource.h"

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

	// Signal the D2D thread to render a new frame. Safe to call from any thread.
	void RequestDraw(bool redraw = false);

	// UI-thread only: forward the SwapChainPanel size-changed event.
	void SizeChanged(
		winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender,
		winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e);

	// UI-thread only: forward the SwapChainPanel composition-scale-changed
	// event. Fires when the window moves to a monitor with a different DPI.
	void CompositionScaleChanged(
		winrt::WinUINamespace::UI::Xaml::Controls::SwapChainPanel const& sender);

	void SetScrollOffsetX(float x);
	void SetScrollOffsetY(float y);
	float ScrollOffsetX() const;
	float ScrollOffsetY() const;

	// Smooth scrolling: drives an easing animation on the draw thread.
	void StartSmoothScrollY(float targetY);
	void StopSmoothScroll();
	bool IsScrolling() const;
	float SmoothScrollTargetY() const;


	int HoveredResizeColumn() const;
	[[nodiscard]] bool SetHoveredResizeColumn(int index); //return whether hovered column change

	int GetResizeColumnIndex(float x) const;

	float GetViewportWidth() const;
	float GetViewportHeight() const;
	float TotalContentWidth() const;

	int DataCount() const;
	void SetHover(float y);
	std::atomic_int Frames{ 0 };
private:
	void drawThreadProc();
	void draw();
	void drawFull(float scrollOffsetX, float scrollOffsetY, int hoveredResizeColumn, int hoveredRow, float scale);
	void drawPartialHover(int oldRow, int newRow, float scrollOffsetX, float scrollOffsetY, float scale);
	void drawHeader(int hoveredResizeColumn, float scrollOffsetX);
	void drawRows(float scrollOffsetX, float scrollOffsetY, int hoveredRow);
	void drawRowCells(int row, float rowY, float scrollOffsetX, float scale);
	void updateScrollOffsets();
	D2D1_ROUNDED_RECT getResizePillRect(int column, float scrollOffsetX) const;
	D2D_RECT_F getRowRect(int row, float scrollOffsetY, float scale) const;

	void rebuildTextFormatsForScale();
	
	TableTestData m_data;


	winrt::com_ptr<ID2D1Factory1> d2d1Factory = DirectN::CreateD2D1Factory();
	winrt::com_ptr<ID3D11Device> m_d3dDevice = DirectN::CreateD3D11Device();
	winrt::com_ptr<ID2D1DeviceContext> m_d2dContext;
	winrt::com_ptr<IDWriteFactory> m_dwriteFactory = DirectN::CreateDWriteFactory();

	TableLinesCache m_tableLines{ d2d1Factory.get() };
	SwapChainInterop m_swapChain;

	TextLayoutCache m_textLayoutCache{ m_dwriteFactory.get() };
	TableD2DResource m_resource;
public:
	ColumnWidthManager m_columnWidthManager{ m_textLayoutCache, m_resource.m_localTableData };
private:
	std::atomic<float> m_scrollOffsetX{ 0.f };
	std::atomic<float> m_scrollOffsetY{ 0.f };
	//Data-row index under the pointer, or -1 when the pointer is not over a
	//row. Storing the row (not the raw y) both simplifies the hover test in
	//the draw code and gates redraws to actual row transitions.
	int m_hoveredRow{ TableConstants::HoveredRowNone };
	std::atomic<bool> m_initialSizing{ true };
	std::atomic<bool> m_fullRedrawNeeded{ true };

	std::atomic<int> m_hoveredResizeColumn{ TableConstants::ResizeColumnIndexNone };
	int m_sortColumnIndex = -1;

	// Smooth scroll state
	std::atomic<float> m_smoothScrollTargetY{ 0.f };
	std::atomic<bool> m_drawRequest{ false };
	std::atomic<bool> m_swapChainDirty{ false };
	std::atomic<bool> m_stopRequested{ false };
	std::atomic<bool> m_isScrolling{ false };

	int m_prevHoveredRow{ TableConstants::HoveredRowNone };

	//These are for clearing up the back buffers because BufferCount = 2]
	//We need to explicitly redrawing the hovered row with the previous buffer
	int m_lastPartialOldRow{ TableConstants::HoveredRowNone };
	int m_lastPartialNewRow{ TableConstants::HoveredRowNone };

	//Draw-thread-only. Floor of the last scroll offset for which the
	//scrollbar-thumb update was dispatched to the UI thread. Gates
	//sub-pixel-equivalent redundant hops during smooth-scroll animation.
	//Sentinel ensures the first frame dispatches.
	int m_cachedScrollBarY{ -1 };

	//Writer (UI thread) fills startY/endY/startTime and then stores
	//isPending=true with release ordering. Reader (draw thread) swaps the
	//flag with acquire ordering and reads the fields — no mutex needed.
	ScrollRequest m_pendingScrollRequest;
	//Draw-thread-only snapshot. Its isPending is never touched.
	ScrollRequest m_activeScrollRequest;

	winrt::PackageRoot::implementation::Table& m_table_ref;

	std::thread m_drawThread;
};
