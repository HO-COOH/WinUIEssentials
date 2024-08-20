#pragma once

#include "PopupMenuFlyoutItem.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct PopupMenuFlyoutItem : PopupMenuFlyoutItemT<PopupMenuFlyoutItem>
    {
        PopupMenuFlyoutItem() = default;

#pragma region Inheirted from PopupMenuFlyoutItemBase
        winrt::WinUI3Package::PopupMenuFlyoutItemType Type();
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
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_iconProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_textProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_commandProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_commandParameterProperty;
        winrt::event<winrt::Microsoft::UI::Xaml::RoutedEventHandler> m_clickEvent;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct PopupMenuFlyoutItem : PopupMenuFlyoutItemT<PopupMenuFlyoutItem, implementation::PopupMenuFlyoutItem>
    {
    };
}
