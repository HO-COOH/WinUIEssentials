#pragma once

#include "ShimmerPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ShimmerPage : ShimmerPageT<ShimmerPage>
    {
        ShimmerPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ShimmerPage : ShimmerPageT<ShimmerPage, implementation::ShimmerPage>
    {
    };
}
