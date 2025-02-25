#pragma once

#include "PopupMenuFlyoutItem.h"
#include "TogglePopupMenuFlyoutItem.g.h"
#include "PopupMenuFlyoutItemImplBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct TogglePopupMenuFlyoutItem : TogglePopupMenuFlyoutItemT<TogglePopupMenuFlyoutItem, PopupMenuFlyoutItem>
    {
        TogglePopupMenuFlyoutItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        winrt::WinUI3Package::PopupMenuFlyoutItemType Type() override;
#pragma endregion

        bool IsChecked();
        void IsChecked(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsCheckedProperty();
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isCheckedProperty;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TogglePopupMenuFlyoutItem : TogglePopupMenuFlyoutItemT<TogglePopupMenuFlyoutItem, implementation::TogglePopupMenuFlyoutItem>
    {
    };
}
