#pragma once

#include "PopupMenuFlyoutSubItem.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutSubItem : PopupMenuFlyoutSubItemT<PopupMenuFlyoutSubItem>
    {
        PopupMenuFlyoutSubItem() = default;

        winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> Items()
        {
            return nullptr;
        }

        void Items(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> value)
        {

        }
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutSubItem : PopupMenuFlyoutSubItemT<PopupMenuFlyoutSubItem, implementation::PopupMenuFlyoutSubItem>
    {
    };
}
