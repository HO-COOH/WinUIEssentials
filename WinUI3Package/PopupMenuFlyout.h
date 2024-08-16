#pragma once

#include "PopupMenuFlyout.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyout : PopupMenuFlyoutT<PopupMenuFlyout>
    {
        PopupMenuFlyout() = default;

        winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> Items();
        void Items(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> value);
    private:

    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyout : PopupMenuFlyoutT<PopupMenuFlyout, implementation::PopupMenuFlyout>
    {
    };
}
