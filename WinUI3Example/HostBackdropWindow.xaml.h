#pragma once

#include "HostBackdropWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct HostBackdropWindow : HostBackdropWindowT<HostBackdropWindow>
    {
        HostBackdropWindow();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct HostBackdropWindow : HostBackdropWindowT<HostBackdropWindow, implementation::HostBackdropWindow>
    {
    };
}
