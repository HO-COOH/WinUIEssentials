#pragma once

#include "ThemeListenerPage.g.h"
#include <ThemeListener.h>

namespace winrt::WinUI3Example::implementation
{
    struct ThemeListenerPage : ThemeListenerPageT<ThemeListenerPage>
    {
        ThemeListenerPage() = default;
        static winrt::hstring ElementThemeToString(winrt::Microsoft::UI::Xaml::ElementTheme theme);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ThemeListenerPage : ThemeListenerPageT<ThemeListenerPage, implementation::ThemeListenerPage>
    {
    };
}
