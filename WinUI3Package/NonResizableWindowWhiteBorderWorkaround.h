#pragma once

#include "NonResizableWindowWhiteBorderWorkaround.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct NonResizableWindowWhiteBorderWorkaround : NonResizableWindowWhiteBorderWorkaroundT<NonResizableWindowWhiteBorderWorkaround>
    {
        NonResizableWindowWhiteBorderWorkaround() = default;

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& value);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct NonResizableWindowWhiteBorderWorkaround : NonResizableWindowWhiteBorderWorkaroundT<NonResizableWindowWhiteBorderWorkaround, implementation::NonResizableWindowWhiteBorderWorkaround>
    {
    };
}
