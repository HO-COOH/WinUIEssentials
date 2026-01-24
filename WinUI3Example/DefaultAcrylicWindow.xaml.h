#pragma once

#include "DefaultAcrylicWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultAcrylicWindow : DefaultAcrylicWindowT<DefaultAcrylicWindow>
    {
        DefaultAcrylicWindow() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultAcrylicWindow : DefaultAcrylicWindowT<DefaultAcrylicWindow, implementation::DefaultAcrylicWindow>
    {
    };
}
