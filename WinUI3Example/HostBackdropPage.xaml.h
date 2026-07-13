#pragma once

#include "HostBackdropPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct HostBackdropPage : HostBackdropPageT<HostBackdropPage>
    {
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct HostBackdropPage : HostBackdropPageT<HostBackdropPage, implementation::HostBackdropPage>
    {
    };
}
