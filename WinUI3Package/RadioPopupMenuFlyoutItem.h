#pragma once

#include "PopupMenuFlyoutItem.h"
#include "RadioPopupMenuFlyoutItem.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "PopupMenuFlyoutItemImplBase.h"

class RadioPopupMenuItemGroup;

namespace winrt::WinUI3Package::implementation
{
    struct RadioPopupMenuFlyoutItem : RadioPopupMenuFlyoutItemT<RadioPopupMenuFlyoutItem, PopupMenuFlyoutItem>, EnsureDependencyProperty<RadioPopupMenuFlyoutItem>
    {
        static void EnsureDependencyProperties();
        RadioPopupMenuFlyoutItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        winrt::WinUI3Package::PopupMenuFlyoutItemType Type();
#pragma endregion

        bool IsChecked();
        void IsChecked(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsCheckedProperty();

        winrt::hstring GroupName();
        void GroupName(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty GroupNameProperty();

        void SetGroupHelper(RadioPopupMenuItemGroup& groupHelper);
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_isCheckedProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_groupNameProperty = nullptr;
        RadioPopupMenuItemGroup* m_groupHelper{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct RadioPopupMenuFlyoutItem : RadioPopupMenuFlyoutItemT<RadioPopupMenuFlyoutItem, implementation::RadioPopupMenuFlyoutItem>
    {
    };
}
