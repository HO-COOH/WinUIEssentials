#pragma once

#include "DefaultWindowCaptionButtonWorkaround.g.h"
#include "SupportThemeToggle.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultWindowCaptionButtonWorkaround : DefaultWindowCaptionButtonWorkaroundT<DefaultWindowCaptionButtonWorkaround>, public SupportThemeToggle<DefaultWindowCaptionButtonWorkaround>
    {
        DefaultWindowCaptionButtonWorkaround()
        {
            ExtendsContentIntoTitleBar(true);
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultWindowCaptionButtonWorkaround : DefaultWindowCaptionButtonWorkaroundT<DefaultWindowCaptionButtonWorkaround, implementation::DefaultWindowCaptionButtonWorkaround>
    {
    };
}
