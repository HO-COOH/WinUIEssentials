#pragma once

#include "Table.g.h"
#include "SwapChainInterop.h"
#include "DirectN.h"
#include "TableTestData.hpp"
#include "TextLayoutCache.h"
#include <mutex>
#include <condition_variable>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

namespace winrt::WinUI3Package::implementation
{
    struct Table : TableT<Table>
    {
        Table();

        void ClickHandler(Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
        void VerticalScrollBar_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
    private:
		winrt::com_ptr<ID3D11Device> m_d3dDevice = DirectN::CreateD3D11Device();
		winrt::com_ptr<ID2D1DeviceContext> m_d2dContext;
        winrt::com_ptr<IDWriteFactory>  m_dwriteFactory = DirectN::CreateDWriteFactory();

        SwapChainInterop m_swapChain;
		winrt::Microsoft::UI::Dispatching::DispatcherQueue m_dispatcherQueue{ nullptr };

        //text
        winrt::com_ptr<IDWriteTextFormat> m_headerTextFormat;
		winrt::com_ptr<IDWriteTextFormat> m_cellTextFormat;
        TextLayoutCache m_textLayoutCache{ m_dwriteFactory.get() };

        //brushes
        winrt::com_ptr<ID2D1SolidColorBrush> m_textBrush;
		winrt::com_ptr<ID2D1SolidColorBrush> m_backgroundBrush;
		winrt::com_ptr<ID2D1SolidColorBrush> m_alternateBackgroundBrush;

        //scrolling
        float m_scrollOffsetX{};
        float m_scrollOffsetY{};
        float m_smoothScrollTargetY{};
        int m_sortColumnIndex{ -1 };
        winrt::Microsoft::UI::Xaml::Controls::Primitives::ScrollBar m_verticalScrollBar{ nullptr };
		winrt::Microsoft::UI::Xaml::Controls::Primitives::ScrollBar m_horizontalScrollBar{ nullptr };
        bool m_isUpdatingVerticalScrollBarInCode{};
		bool m_isUpdatingHorizontalScrollBarInCode{};
        std::atomic_bool m_isScrolling{};
		void updateVerticalScrollBar();
        void updateHorizontalScrollBar();
		void hideVerticalScrollBar();
		void hideHorizontalScrollBar();
        void stopSmoothScroll();
		void startSmoothScroll(float targetY);
        float getViewportHeight() const;
		float getViewportWidth() const;
        void scrollThreadProc(std::stop_token stopToken);

        struct ScrollRequest
        {
            float startY;
            float endY;
            std::chrono::steady_clock::time_point startTime;
            bool isPending = false;
        };
        ScrollRequest m_scrollRequest;

		std::mutex m_scrollMutex;
        std::condition_variable m_scrollEvent;
        std::jthread m_smoothScrollThread;


        //data
		TableTestData m_data;

        void draw();
        void drawHeader();
        void drawRows();
    public:
       
        void SwapChainPanel_PointerWheelChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void HorizontalScrollBar_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Table : TableT<Table, implementation::Table>
    {
    };
}
