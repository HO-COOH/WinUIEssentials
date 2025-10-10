#include "pch.h"
#include "WindowCaptionButtonThemeWorkaround.h"
#if __has_include("WindowCaptionButtonThemeWorkaround.g.cpp")
#include "WindowCaptionButtonThemeWorkaround.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    WindowCaptionButtonThemeWorkaround::WindowCaptionButtonThemeWorkaround()
    {
        ActualThemeChanged([this](auto&&...) {
            setCaptionButtonTheme(ActualTheme());
        });
    }

    winrt::Microsoft::UI::Xaml::Window WindowCaptionButtonThemeWorkaround::Window()
    {
        return m_window;
    }

    void WindowCaptionButtonThemeWorkaround::Window(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        m_window = window;
        m_titleBar = m_window.AppWindow().TitleBar();
        setCaptionButtonTheme(ActualTheme());
    }

    void WindowCaptionButtonThemeWorkaround::setCaptionButtonTheme(winrt::Microsoft::UI::Xaml::ElementTheme const& theme)
    {
        auto const foreground = theme == winrt::Microsoft::UI::Xaml::ElementTheme::Dark ? winrt::Windows::UI::Colors::White() : winrt::Windows::UI::Colors::Black();
        auto pressedForeground = foreground;
        pressedForeground.A = foreground.A * 0.2;
        m_titleBar.ButtonForegroundColor(foreground);
        m_titleBar.ButtonHoverForegroundColor(foreground);
        m_titleBar.ButtonPressedForegroundColor(pressedForeground);
    }
}
