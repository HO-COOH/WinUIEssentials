#pragma once

#include "DefaultMicaWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultMicaWindow : DefaultMicaWindowT<DefaultMicaWindow>
    {
        DefaultMicaWindow() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultMicaWindow : DefaultMicaWindowT<DefaultMicaWindow, implementation::DefaultMicaWindow>
    {
    };
}
