#pragma once

#include "OriginalWinUI3WindowExtendedWithModernToolTip.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct OriginalWinUI3WindowExtendedWithModernToolTip : OriginalWinUI3WindowExtendedWithModernToolTipT<OriginalWinUI3WindowExtendedWithModernToolTip>
    {
        OriginalWinUI3WindowExtendedWithModernToolTip(bool animate);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct OriginalWinUI3WindowExtendedWithModernToolTip : OriginalWinUI3WindowExtendedWithModernToolTipT<OriginalWinUI3WindowExtendedWithModernToolTip, implementation::OriginalWinUI3WindowExtendedWithModernToolTip>
    {
    };
}
