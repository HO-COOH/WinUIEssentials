#pragma once

#include "PopupMenuFlyoutSubItem.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "PopupMenuFlyoutItemBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutSubItem : PopupMenuFlyoutSubItemT<PopupMenuFlyoutSubItem, PopupMenuFlyoutItemBase>, EnsureDependencyProperty<PopupMenuFlyoutSubItem>
    {
        static void EnsureDependencyProperties();
        PopupMenuFlyoutSubItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        constexpr winrt::WinUI3Package::PopupMenuFlyoutItemType Type() { return winrt::WinUI3Package::PopupMenuFlyoutItemType::SubMenu; }
#pragma endregion

        winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> Items()
        {
            return m_items;
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
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_iconProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_textProperty = nullptr;
        winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> m_items{ winrt::single_threaded_vector<winrt::WinUI3Package::PopupMenuFlyoutItemBase>() };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutSubItem : PopupMenuFlyoutSubItemT<PopupMenuFlyoutSubItem, implementation::PopupMenuFlyoutSubItem>
    {
    };
}
