#pragma once

#include "OriginalWinUI3WindowWithModernToolTip.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct OriginalWinUI3WindowWithModernToolTip : OriginalWinUI3WindowWithModernToolTipT<OriginalWinUI3WindowWithModernToolTip>
    {
        OriginalWinUI3WindowWithModernToolTip(bool animate);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct OriginalWinUI3WindowWithModernToolTip : OriginalWinUI3WindowWithModernToolTipT<OriginalWinUI3WindowWithModernToolTip, implementation::OriginalWinUI3WindowWithModernToolTip>
    {
    };
}
