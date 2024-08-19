#pragma once

#include "PopupMenuFlyoutSubItem.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutSubItem : PopupMenuFlyoutSubItemT<PopupMenuFlyoutSubItem>
    {
        PopupMenuFlyoutSubItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        constexpr winrt::WinUI3Package::PopupMenuFlyoutItemType Type() { return winrt::WinUI3Package::PopupMenuFlyoutItemType::SubMenu; }
#pragma endregion

        winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> Items()
        {
            return nullptr;
        }

        void Items(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> value)
        {

        }

        winrt::Microsoft::UI::Xaml::Controls::IconElement Icon();
        void Icon(winrt::Microsoft::UI::Xaml::Controls::IconElement const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IconProperty();

        winrt::hstring Text();
        void Text(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TextProperty();

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_iconProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_textProperty;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutSubItem : PopupMenuFlyoutSubItemT<PopupMenuFlyoutSubItem, implementation::PopupMenuFlyoutSubItem>
    {
    };
}
