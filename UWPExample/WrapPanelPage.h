#pragma once

#include "WrapPanelPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct WrapPanelPage : WrapPanelPageT<WrapPanelPage>
    {
        winrt::Windows::Foundation::Collections::IObservableVector<UWPExample::PhotoDataItemWithDimension> WrapPanelCollection();
        void ItemControl_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
        void AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void AddFixedBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void SwitchBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<UWPExample::PhotoDataItemWithDimension> m_wrapPanelCollection =
            winrt::single_threaded_observable_vector<UWPExample::PhotoDataItemWithDimension>();
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct WrapPanelPage : WrapPanelPageT<WrapPanelPage, implementation::WrapPanelPage>
    {
    };
}
