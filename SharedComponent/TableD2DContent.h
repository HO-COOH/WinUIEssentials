#pragma once
#include <winrt/base.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
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

namespace winrt::WinUI3Package::implementation
{
	struct Table;
}

class TableD2DContent
{
public:
	TableD2DContent();
	~TableD2DContent();

	TableD2DContent(TableD2DContent const&) = delete;
	TableD2DContent& operator=(TableD2DContent const&) = delete;

	// Called from the WinUI3 UI thread after construction to wire up the
	// swap-chain panel and start the D2D thread. onScrollFrameRendered, if
	// provided, is marshaled to the UI thread after every frame that
	// advanced the smooth-scroll animation, so the caller can keep XAML
	// state (e.g. the scrollbar thumb) in lockstep with the D2D present.
	void Initialize(winrt::WinUI3Package::implementation::Table& table);

	void Stop();

	// Signal the D2D thread to render a new frame. Safe to call from any thread.
	void RequestDraw();

	// UI-thread only: forward the SwapChainPanel size-changed event.
	void SizeChanged(
		winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender,
		winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);

	void SetScrollOffsetX(float x);
	void SetScrollOffsetY(float y);
	float ScrollOffsetX() const;
	float ScrollOffsetY() const;

	// Smooth scrolling: drives an easing animation on the draw thread.
	void StartSmoothScrollY(float targetY);
	void StopSmoothScroll();
	bool IsScrolling() const;
	float SmoothScrollTargetY() const;

	float ColumnWidth(int column) const;
	void SetColumnWidth(int column, float width);

	int HoveredResizeColumn() const;
	[[nodiscard]] bool SetHoveredResizeColumn(int index); //return whether hovered column change

	int GetResizeColumnIndex(float x) const;

	float GetViewportWidth() const;
	float GetViewportHeight() const;
	float TotalContentWidth() const;

	int DataCount() const;

private:
	void drawThreadProc();
	void draw();
	void drawHeader(std::vector<float> const& columnWidths, int hoveredResizeColumn, float scrollOffsetX);
	void drawRows(std::vector<float> const& columnWidths, float scrollOffsetX, float scrollOffsetY);
	D2D1_ROUNDED_RECT getResizePillRect(std::vector<float> const& columnWidths, int column, float scrollOffsetX) const;

	TableTestData m_data;

	winrt::com_ptr<ID3D11Device> m_d3dDevice = DirectN::CreateD3D11Device();
	winrt::com_ptr<ID2D1DeviceContext> m_d2dContext;
	winrt::com_ptr<IDWriteFactory> m_dwriteFactory = DirectN::CreateDWriteFactory();

	SwapChainInterop m_swapChain;

	winrt::com_ptr<IDWriteTextFormat> m_headerTextFormat;
	winrt::com_ptr<IDWriteTextFormat> m_cellTextFormat;
	TextLayoutCache m_textLayoutCache{ m_dwriteFactory.get() };

	winrt::com_ptr<ID2D1SolidColorBrush> m_textBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_backgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_alternateBackgroundBrush;
	winrt::com_ptr<ID2D1SolidColorBrush> m_pillBrush;

	std::atomic<float> m_scrollOffsetX{ 0.f };
	std::atomic<float> m_scrollOffsetY{ 0.f };

	std::vector<std::atomic<float>> m_columnWidths;
	std::atomic<int> m_hoveredResizeColumn{ TableConstants::ResizeColumnIndexNone };
	int m_sortColumnIndex = -1;

	// Smooth scroll state
	std::atomic<bool> m_isScrolling{ false };
	std::atomic<float> m_smoothScrollTargetY{ 0.f };

	std::atomic<bool> m_drawRequest{ false };
	std::atomic<bool> m_swapChainDirty{ false };
	std::atomic<bool> m_stopRequested{ false };

	//Writer (UI thread) fills startY/endY/startTime and then stores
	//isPending=true with release ordering. Reader (draw thread) swaps the
	//flag with acquire ordering and reads the fields — no mutex needed.
	ScrollRequest m_pendingScrollRequest;
	//Draw-thread-only snapshot. Its isPending is never touched.
	ScrollRequest m_activeScrollRequest;

	winrt::Microsoft::UI::Dispatching::DispatcherQueue m_dispatcher{ nullptr };
	winrt::WinUI3Package::implementation::Table* m_table_ref{ nullptr };

	std::thread m_drawThread;
};
