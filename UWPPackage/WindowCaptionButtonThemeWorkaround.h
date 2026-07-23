#pragma once

#include "WindowCaptionButtonThemeWorkaround.g.h"

namespace winrt::UWPPackage::implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround>
    {
        WindowCaptionButtonThemeWorkaround();
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround, implementation::WindowCaptionButtonThemeWorkaround>
    {
    };
}
