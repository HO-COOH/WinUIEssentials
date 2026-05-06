#pragma once

#include "ThemeToggleButton.g.h"

namespace winrt::PackageRoot::implementation
{
    struct ThemeToggleButton : ThemeToggleButtonT<ThemeToggleButton>
    {
        ThemeToggleButton();

        winrt::WinUINamespace::UI::Xaml::FrameworkElement Root();
        void Root(winrt::WinUINamespace::UI::Xaml::FrameworkElement const& value);

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e);
    private:
        winrt::WinUINamespace::UI::Xaml::FrameworkElement m_root{ nullptr };

        int m_themeIndex = 2;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ThemeToggleButton : ThemeToggleButtonT<ThemeToggleButton, implementation::ThemeToggleButton>
    {
    };
}
