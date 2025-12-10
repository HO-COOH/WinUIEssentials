#include "pch.h"
#include "WindowCaptionButtonThemeWorkaround.h"
#if __has_include("WindowCaptionButtonThemeWorkaround.g.cpp")
#include "WindowCaptionButtonThemeWorkaround.g.cpp"
#endif
#include "ThemeSettingsImpl.hpp"
#include "ThemeSettings.h"

namespace winrt::WinUI3Package::implementation
{
    // Moved operators inside the namespace so they are found correctly
    constexpr winrt::Windows::UI::Color operator*(winrt::Windows::UI::Color color, double value)
    {
        return
        {
            static_cast<uint8_t>(color.A * value),
            static_cast<uint8_t>(color.R * value),
            static_cast<uint8_t>(color.G * value),
            static_cast<uint8_t>(color.B * value)
        };
    }

    constexpr winrt::Windows::UI::Color operator+(winrt::Windows::UI::Color lhs, winrt::Windows::UI::Color rhs)
    {
        return
        {
            static_cast<uint8_t>(lhs.A + rhs.A),
            static_cast<uint8_t>(lhs.R + rhs.R),
            static_cast<uint8_t>(lhs.G + rhs.G),
            static_cast<uint8_t>(lhs.B + rhs.B)
        };
    }

    WindowCaptionButtonThemeWorkaround::WindowCaptionButtonThemeWorkaround()
    {
        ActualThemeChanged([this](auto&&...) {
            setCaptionButtonTheme(ActualTheme());
        });
    }

    winrt::Microsoft::UI::Xaml::Window WindowCaptionButtonThemeWorkaround::Window()
    {
        return nullptr;
    }

    void WindowCaptionButtonThemeWorkaround::Window(winrt::Microsoft::UI::Xaml::Window const& window)
    {
        m_titleBar = window.AppWindow().TitleBar();
        setCaptionButtonTheme(ActualTheme());
    }

    // Alpha does not seems to be respected, so we do alpha blending ourselves
    constexpr winrt::Windows::UI::Color getPressedForeground(winrt::Windows::UI::Color foreground, winrt::Windows::UI::Color background)
    {
        return (foreground * 0.5) + (background * 0.5);
    }

    constexpr bool isColorLight(Windows::UI::Color clr)
    {
        return (((5 * clr.G) + (2 * clr.R) + clr.B) > (8 * 128));
    }

    void WindowCaptionButtonThemeWorkaround::setCaptionButtonTheme(winrt::Microsoft::UI::Xaml::ElementTheme const& theme)
    {
        try
        {
            auto const foreground = theme == winrt::Microsoft::UI::Xaml::ElementTheme::Dark ? winrt::Windows::UI::Colors::White() : winrt::Windows::UI::Colors::Black();
            m_titleBar.ButtonForegroundColor(foreground);


            if (ThemeSettingsImpl::ShowAccentColorOnTitleBarsAndWindowBorders())
            {
                auto const hoverBackground = winrt::WinUI3Package::implementation::ThemeSettings::Instance().AccentColor();
                m_titleBar.ButtonHoverBackgroundColor(hoverBackground);
                m_titleBar.ButtonPressedBackgroundColor(hoverBackground);

                auto const hoverForeground = isColorLight(hoverBackground) ? winrt::Windows::UI::Colors::Black() : winrt::Windows::UI::Colors::White();
                m_titleBar.ButtonHoverForegroundColor(hoverForeground);
                m_titleBar.ButtonPressedForegroundColor(getPressedForeground(hoverForeground, hoverBackground));
            }
            else
            {
                /*
                    when ShowAccentColorOnTitleBarsAndWindowBorders is false, the caption button colors are hard-coded:
                                        hover background     pressed background          foreground
                        light theme:    #E9E9E9                     #EDEDED                 black
                        dark theme:     #2D2D2D                     #292929                 white
                */
                auto const hoverBackground = theme == winrt::Microsoft::UI::Xaml::ElementTheme::Dark ?
                    winrt::Windows::UI::Color{ .A = 0xFF, .R = 0x2D, .G = 0x2D, .B = 0x2D } :
                    winrt::Windows::UI::Color{ .A = 0xFF, .R = 0xE9, .G = 0xE9, .B = 0xE9 };

                auto const pressedBackground = theme == winrt::Microsoft::UI::Xaml::ElementTheme::Dark ?
                    winrt::Windows::UI::Color{ .A = 0xFF, .R = 0x29, .G = 0x29, .B = 0x29 } :
                    winrt::Windows::UI::Color{ .A = 0xFF, .R = 0xED, .G = 0xED, .B = 0xED };

                auto const foreground = theme == winrt::Microsoft::UI::Xaml::ElementTheme::Dark ?
                    winrt::Windows::UI::Colors::White() : winrt::Windows::UI::Colors::Black();

                m_titleBar.ButtonHoverBackgroundColor(hoverBackground);
                m_titleBar.ButtonHoverForegroundColor(foreground);
                m_titleBar.ButtonPressedForegroundColor(getPressedForeground(foreground, pressedBackground));
                m_titleBar.ButtonPressedBackgroundColor(pressedBackground);
            }
        }
        catch (...)
        {
            //prevent m_titleBar was closed for unexpected reasons, like the window is closed but the reference is still there
        }
    }
}
