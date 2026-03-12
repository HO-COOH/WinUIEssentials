#pragma once

#include "PopupMenuFlyoutItem.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "PopupMenuFlyoutItemBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutItem : PopupMenuFlyoutItemT<PopupMenuFlyoutItem, PopupMenuFlyoutItemBase>, EnsureDependencyProperty<PopupMenuFlyoutItem>
    {
        static void EnsureDependencyProperties();
        PopupMenuFlyoutItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        virtual winrt::WinUI3Package::PopupMenuFlyoutItemType Type();
#pragma endregion

        winrt::Microsoft::UI::Xaml::Controls::IconElement Icon();
        void Icon(winrt::Microsoft::UI::Xaml::Controls::IconElement const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IconProperty();

        winrt::hstring Text();
        void Text(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TextProperty();

        winrt::Microsoft::UI::Xaml::Input::ICommand Command();
        void Command(winrt::Microsoft::UI::Xaml::Input::ICommand const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty CommandProperty();

        winrt::Windows::Foundation::IInspectable CommandParameter();
        void CommandParameter(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty CommandParameterProperty();

        winrt::event_token Click(winrt::Microsoft::UI::Xaml::RoutedEventHandler const& handler);
        void Click(winrt::event_token const& token);
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_iconProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_textProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_commandProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_commandParameterProperty = nullptr;

        winrt::event<winrt::Microsoft::UI::Xaml::RoutedEventHandler> m_clickEvent;

        friend class PopupMenu;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutItem : PopupMenuFlyoutItemT<PopupMenuFlyoutItem, implementation::PopupMenuFlyoutItem>
    {
    };
}
