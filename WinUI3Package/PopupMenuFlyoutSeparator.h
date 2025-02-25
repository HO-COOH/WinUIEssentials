#pragma once

#include "PopupMenuFlyoutSeparator.g.h"
#include "PopupMenuFlyoutItemBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutSeparator : PopupMenuFlyoutSeparatorT<PopupMenuFlyoutSeparator, PopupMenuFlyoutItemBase>
    {
        PopupMenuFlyoutSeparator() = default;
        
#pragma region Inheirted from PopupMenuFlyoutItemBase
        winrt::WinUI3Package::PopupMenuFlyoutItemType Type() override;
#pragma endregion
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutSeparator : PopupMenuFlyoutSeparatorT<PopupMenuFlyoutSeparator, implementation::PopupMenuFlyoutSeparator>
    {
    };
}
