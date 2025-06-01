#pragma once

#include "WrapPanelPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WrapPanelPage : WrapPanelPageT<WrapPanelPage>
    {
        WrapPanelPage() = default;

        winrt::Windows::Foundation::Collections::IObservableVector<WinUI3Example::PhotoDataItemWithDimension> WrapPanelCollection();
        void ItemControl_ItemClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::ItemClickEventArgs const& e);
        void AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void AddFixedBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SwitchBtn_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<WinUI3Example::PhotoDataItemWithDimension> m_wrapPanelCollection =
            winrt::single_threaded_observable_vector<WinUI3Example::PhotoDataItemWithDimension>();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WrapPanelPage : WrapPanelPageT<WrapPanelPage, implementation::WrapPanelPage>
    {
    };
}
