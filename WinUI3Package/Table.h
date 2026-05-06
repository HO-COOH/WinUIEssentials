#pragma once

#include "Table.g.h"
#include "TableD2DContent.h"
#include "CachedScrollBar.h"
#include "ResizeRequest.h"
#include "TableConstants.hpp"
#include "CachedCursor.hpp"
#include <include/PropertyChangeHelper.hpp>

namespace winrt::WinUI3Package::implementation
{
    struct Table : TableT<Table>, CachedCursor<Table>, MvvmHelper::PropertyChangeHelper<Table>
    {
        Table();

        void SwapChainPanel_SizeChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
        void SwapChainPanel_CompositionScaleChanged(winrt::Microsoft::UI::Xaml::Controls::SwapChainPanel const& sender, winrt::Windows::Foundation::IInspectable const& args);
        void VerticalScrollBar_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
        void HorizontalScrollBar_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
        void SwapChainPanel_PointerWheelChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SwapChainPanel_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SwapChainPanel_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void SwapChainPanel_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);

        void updateVerticalScrollBar(float scrollOffsetY);
        int Fps();
        int DataCount();
        void DataCount(int value);
    private:
        TableD2DContent m_d2dContent{ *this };

        //Request a redraw and immediately refresh the scrollbars.
        //UI-thread only.
        void requestDraw(bool redraw = false);

        //scrollbars (XAML - UI thread only)
        CachedScrollBar m_verticalScrollBarCache;
        CachedScrollBar m_horizontalScrollBarCache;
        bool m_isUpdatingVerticalScrollBarInCode{};
        bool m_isUpdatingHorizontalScrollBarInCode{};

        void updateHorizontalScrollBar(float scrollOffsetX);
        void updateScrollBars();
        void hideVerticalScrollBar();
        void hideHorizontalScrollBar();

        //resizing
        ResizeRequest m_resizeRequest;
        
        //fps
        winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_fpsTimer{ nullptr };
        float m_fps{};
    public:
        void SwapChainPanel_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Table : TableT<Table, implementation::Table>
    {
    };
}
