#pragma once

#include "TablePage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TablePage : TablePageT<TablePage>
    {
        TablePage() = default;

        void OnLoaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnUnloaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void OnScrollViewerSizeChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& e);
        
    private:
        void syncHeight();

        winrt::Microsoft::UI::Xaml::Controls::ScrollViewer m_scrollViewer{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker{};
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TablePage : TablePageT<TablePage, implementation::TablePage>
    {
    };
}
