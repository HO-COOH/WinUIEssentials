#pragma once

#include "PopupMenuFlyoutItem.h"
#include "TogglePopupMenuFlyoutItem.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "PopupMenuFlyoutItemImplBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct TogglePopupMenuFlyoutItem : TogglePopupMenuFlyoutItemT<TogglePopupMenuFlyoutItem, PopupMenuFlyoutItem>, EnsureDependencyProperty<TogglePopupMenuFlyoutItem>
    {
        static void EnsureDependencyProperties();
        TogglePopupMenuFlyoutItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        winrt::WinUI3Package::PopupMenuFlyoutItemType Type() override;
#pragma endregion

        bool IsChecked();
        void IsChecked(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsCheckedProperty();
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_isCheckedProperty = nullptr;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TogglePopupMenuFlyoutItem : TogglePopupMenuFlyoutItemT<TogglePopupMenuFlyoutItem, implementation::TogglePopupMenuFlyoutItem>
    {
    };
}
