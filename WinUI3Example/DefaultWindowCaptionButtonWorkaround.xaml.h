#pragma once

#include "DefaultWindowCaptionButtonWorkaround.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultWindowCaptionButtonWorkaround : DefaultWindowCaptionButtonWorkaroundT<DefaultWindowCaptionButtonWorkaround>
    {
        DefaultWindowCaptionButtonWorkaround();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultWindowCaptionButtonWorkaround : DefaultWindowCaptionButtonWorkaroundT<DefaultWindowCaptionButtonWorkaround, implementation::DefaultWindowCaptionButtonWorkaround>
    {
    };
}
