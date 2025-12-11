#pragma once

#include "ThemeToggleButton.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ThemeToggleButton : ThemeToggleButtonT<ThemeToggleButton>
    {
        ThemeToggleButton();

        winrt::Microsoft::UI::Xaml::FrameworkElement Root();
        void Root(winrt::Microsoft::UI::Xaml::FrameworkElement const& value);

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    private:
        winrt::Microsoft::UI::Xaml::FrameworkElement m_root{ nullptr };

        int m_themeIndex = 2;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ThemeToggleButton : ThemeToggleButtonT<ThemeToggleButton, implementation::ThemeToggleButton>
    {
    };
}
