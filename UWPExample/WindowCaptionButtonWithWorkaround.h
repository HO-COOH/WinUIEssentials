#pragma once

#include "WindowCaptionButtonWithWorkaround.g.h"

namespace winrt::UWPExample::implementation
{
    struct WindowCaptionButtonWithWorkaround : WindowCaptionButtonWithWorkaroundT<WindowCaptionButtonWithWorkaround>
    {
        WindowCaptionButtonWithWorkaround();
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct WindowCaptionButtonWithWorkaround : WindowCaptionButtonWithWorkaroundT<WindowCaptionButtonWithWorkaround, implementation::WindowCaptionButtonWithWorkaround>
    {
    };
}
