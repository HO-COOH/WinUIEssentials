#pragma once

#include "ShimmerPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ShimmerPage : ShimmerPageT<ShimmerPage>
    {
        void Image_ImageOpened(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ShimmerPage : ShimmerPageT<ShimmerPage, implementation::ShimmerPage>
    {
    };
}
