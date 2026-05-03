#pragma once
#include <winrt/base.h>
#include <winrt/Microsoft.UI.Dispatching.h>
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

namespace winrt
{
	namespace WinUI3Package::implementation
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
	winrt::Microsoft::UI::Dispatching::DispatcherQueue m_dispatcher{ nullptr };

	TableD2DContent(winrt::WinUI3Package::implementation::Table& table);
	~TableD2DContent();

	TableD2DContent(TableD2DContent const&) = delete;
	TableD2DContent& operator=(TableD2DContent const&) = delete;

	void Stop();

	// Signal the D2D thread to render a new frame. Safe to call from any thread.
	void RequestDraw();

	// UI-thread only: forward the SwapChainPanel size-changed event.
	void SizeChanged(
		winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender,
		winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);

	// UI-thread only: forward the SwapChainPanel composition-scale-changed
	// event. Fires when the window moves to a monitor with a different DPI.
	void CompositionScaleChanged(
		winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender);

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
	[[nodiscard]] bool SetHover(float y);
private:
	void drawThreadProc();
	void draw();
	void drawHeader(int hoveredResizeColumn, float scrollOffsetX);
	void drawRows(float scrollOffsetX, float scrollOffsetY);
	D2D1_ROUNDED_RECT getResizePillRect(int column, float scrollOffsetX) const;

	//Draw-thread only. Recreates text formats (and invalidates the layout
	//cache) so glyph pixel size matches the current composition scale.
	void rebuildTextFormatsForScale(float scale);

	TableTestData m_data;

	winrt::com_ptr<ID3D11Device> m_d3dDevice = DirectN::CreateD3D11Device();
	winrt::com_ptr<ID2D1DeviceContext> m_d2dContext;
	winrt::com_ptr<IDWriteFactory> m_dwriteFactory = DirectN::CreateDWriteFactory();

	SwapChainInterop m_swapChain;

	TextLayoutCache m_textLayoutCache{ m_dwriteFactory.get() };
public:
	ColumnWidthManager m_columnWidthManager{ m_textLayoutCache };
private:
	winrt::com_ptr<ID2D1SolidColorBrush> m_textBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_backgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_alternateBackgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_pillBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_hoverBrush;

	std::atomic<float> m_scrollOffsetX{ 0.f };
	std::atomic<float> m_scrollOffsetY{ 0.f };
	//Data-row index under the pointer, or -1 when the pointer is not over a
	//row. Storing the row (not the raw y) both simplifies the hover test in
	//the draw code and gates redraws to actual row transitions.
	std::atomic<int> m_hoveredRow{ TableConstants::HoveredRowNone };
	std::atomic<bool> m_initialSizing{ true };


	std::atomic<int> m_hoveredResizeColumn{ TableConstants::ResizeColumnIndexNone };
	int m_sortColumnIndex = -1;

	// Smooth scroll state
	std::atomic<float> m_smoothScrollTargetY{ 0.f };
	std::atomic<bool> m_drawRequest{ false };
	std::atomic<bool> m_swapChainDirty{ false };
	std::atomic<bool> m_stopRequested{ false };
	std::atomic<bool> m_isScrolling{ false };

	//Draw-thread-only. Last scale the text formats were built for.
	//Sentinel so the first frame after startup always rebuilds.
	float m_textFormatScale{ -1.f };

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

	winrt::WinUI3Package::implementation::Table& m_table_ref;

	std::thread m_drawThread;
};
