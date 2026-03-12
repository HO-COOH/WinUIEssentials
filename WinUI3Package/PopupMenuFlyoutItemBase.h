#pragma once

#include "PopupMenuFlyoutItemBase.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "PopupMenuFlyoutItemImplBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutItemBase : PopupMenuFlyoutItemBaseT<PopupMenuFlyoutItemBase>, PopupMenuFlyoutItemImplBase, EnsureDependencyProperty<PopupMenuFlyoutItemBase>
    {
        static void EnsureDependencyProperties();
        PopupMenuFlyoutItemBase() = default;

        virtual winrt::WinUI3Package::PopupMenuFlyoutItemType Type()
        {
            return winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutItem;
        }

        winrt::Microsoft::UI::Xaml::Visibility Visibility();
        void Visibility(winrt::Microsoft::UI::Xaml::Visibility value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty VisibilityProperty();

        bool IsEnabled();
        void IsEnabled(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsEnabledProperty();
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_visibilityProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_isEnabledProperty = nullptr;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutItemBase : PopupMenuFlyoutItemBaseT<PopupMenuFlyoutItemBase, implementation::PopupMenuFlyoutItemBase>
    {
    };
}
