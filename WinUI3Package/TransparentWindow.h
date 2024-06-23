#pragma once

#include "TransparentWindow.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct TransparentWindow : TransparentWindowT<TransparentWindow>
    {
        TransparentWindow();

    private:
        static void configureAppWindow(winrt::Microsoft::UI::Windowing::AppWindow const& appWindow);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TransparentWindow : TransparentWindowT<TransparentWindow, implementation::TransparentWindow>
    {
    };
}
