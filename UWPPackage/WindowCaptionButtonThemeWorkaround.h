#pragma once

#include "WindowCaptionButtonThemeWorkaround.g.h"
#include <winrt/Windows.UI.ViewManagement.h>

namespace winrt::UWPPackage::implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround>
    {
        WindowCaptionButtonThemeWorkaround();

    private:
        void setCaptionButtonTheme(winrt::Windows::UI::Xaml::ElementTheme const& theme);

        winrt::Windows::UI::ViewManagement::ApplicationViewTitleBar m_titleBar{ nullptr };
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct WindowCaptionButtonThemeWorkaround : WindowCaptionButtonThemeWorkaroundT<WindowCaptionButtonThemeWorkaround, implementation::WindowCaptionButtonThemeWorkaround>
    {
    };
}
