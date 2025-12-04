#pragma once

#include "WindowCaptionButtonThemeWorkaround.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include "ThemeListener.h"

namespace winrt::WinUI3Package::implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround>
    {
        WindowCaptionButtonThemeWorkaround();

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& window);
    private:
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar m_titleBar{ nullptr };
        void setCaptionButtonTheme(winrt::Microsoft::UI::Xaml::ElementTheme const& theme);

        ThemeListener::Token m_token = ThemeListener::Add([this]() {
            setCaptionButtonTheme(ActualTheme());
        });
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround, implementation::WindowCaptionButtonThemeWorkaround>
    {
    };
}
