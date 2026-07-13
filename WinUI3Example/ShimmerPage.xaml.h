#pragma once

#include "ShimmerPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ShimmerPage : ShimmerPageT<ShimmerPage>
    {

        void Image_ImageOpened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ShimmerPage : ShimmerPageT<ShimmerPage, implementation::ShimmerPage>
    {
    };
}
