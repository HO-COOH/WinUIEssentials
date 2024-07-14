#pragma once

#include "TransparentWindow.g.h"
#include <winrt/Microsoft.UI.Xaml.Markup.h>
namespace winrt::WinUI3Package::implementation
{
    struct TransparentWindow : TransparentWindowT<TransparentWindow>
    {
        TransparentWindow();

        static void configureAppWindow(winrt::Microsoft::UI::Windowing::AppWindow const& appWindow);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TransparentWindow : TransparentWindowT<TransparentWindow, implementation::TransparentWindow>
    {
    };
}
