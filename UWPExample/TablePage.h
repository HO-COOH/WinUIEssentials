#pragma once

#include "TablePage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TablePage : TablePageT<TablePage>
    {

        void OnLoaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void OnUnloaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void OnScrollViewerSizeChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Windows::UI::Xaml::SizeChangedEventArgs const& e);

    private:
        void syncHeight();

        winrt::Windows::UI::Xaml::Controls::ScrollViewer m_scrollViewer{ nullptr };
        winrt::Windows::UI::Xaml::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker{};
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TablePage : TablePageT<TablePage, implementation::TablePage>
    {
    };
}
