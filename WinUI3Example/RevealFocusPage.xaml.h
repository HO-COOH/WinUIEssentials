#pragma once

#include "RevealFocusPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct RevealFocusPage : RevealFocusPageT<RevealFocusPage>
    {
        RevealFocusPage() = default;


        void OnNavigatedTo(winrt::Microsoft::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void BaseListView_ContainerContentChanging(
            winrt::Microsoft::UI::Xaml::Controls::ListViewBase const& sender,
            winrt::Microsoft::UI::Xaml::Controls::ContainerContentChangingEventArgs const& args);
        static std::vector<winrt::WinUI3Example::Contact> GetContactAsync();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct RevealFocusPage : RevealFocusPageT<RevealFocusPage, implementation::RevealFocusPage>
    {
    };
}
