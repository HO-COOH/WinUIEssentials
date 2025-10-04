#pragma once

#include "WindowCaptionButtonThemeWorkaround.g.h"
#include <winrt/Microsoft.UI.Windowing.h>

namespace winrt::WinUI3Package::implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround>
    {
        WindowCaptionButtonThemeWorkaround();

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& window);

    private:
        winrt::Microsoft::UI::Xaml::Window m_window{ nullptr };
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar m_titleBar{ nullptr };
        void setCaptionButtonTheme(winrt::Microsoft::UI::Xaml::ElementTheme const& theme);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround, implementation::WindowCaptionButtonThemeWorkaround>
    {
    };
}
