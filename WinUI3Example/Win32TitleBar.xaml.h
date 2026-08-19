#pragma once

#include "Win32TitleBar.g.h"
#include <dwmapi.h>

namespace winrt::WinUI3Example::implementation
{
    struct Win32TitleBar : Win32TitleBarT<Win32TitleBar>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct Win32TitleBar : Win32TitleBarT<Win32TitleBar, implementation::Win32TitleBar>
    {
    };
}
