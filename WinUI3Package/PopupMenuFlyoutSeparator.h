#pragma once

#include "PopupMenuFlyoutSeparator.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutSeparator : PopupMenuFlyoutSeparatorT<PopupMenuFlyoutSeparator>
    {
        PopupMenuFlyoutSeparator() = default;
        
#pragma region Inheirted from PopupMenuFlyoutItemBase
        winrt::WinUI3Package::PopupMenuFlyoutItemType Type();
#pragma endregion
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutSeparator : PopupMenuFlyoutSeparatorT<PopupMenuFlyoutSeparator, implementation::PopupMenuFlyoutSeparator>
    {
    };
}
