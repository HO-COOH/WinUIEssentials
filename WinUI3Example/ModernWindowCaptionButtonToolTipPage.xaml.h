#pragma once

#include "ModernWindowCaptionButtonToolTipPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ModernWindowCaptionButtonToolTipPage : ModernWindowCaptionButtonToolTipPageT<ModernWindowCaptionButtonToolTipPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ModernWindowCaptionButtonToolTipPage : ModernWindowCaptionButtonToolTipPageT<ModernWindowCaptionButtonToolTipPage, implementation::ModernWindowCaptionButtonToolTipPage>
    {
    };
}
