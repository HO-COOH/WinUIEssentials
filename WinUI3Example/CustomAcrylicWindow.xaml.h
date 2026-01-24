#pragma once

#include "CustomAcrylicWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CustomAcrylicWindow : CustomAcrylicWindowT<CustomAcrylicWindow>
    {
        CustomAcrylicWindow() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CustomAcrylicWindow : CustomAcrylicWindowT<CustomAcrylicWindow, implementation::CustomAcrylicWindow>
    {
    };
}
