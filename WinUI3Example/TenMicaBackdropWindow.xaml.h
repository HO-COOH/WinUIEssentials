#pragma once

#include "TenMicaBackdropWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TenMicaBackdropWindow : TenMicaBackdropWindowT<TenMicaBackdropWindow>
    {
        TenMicaBackdropWindow();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TenMicaBackdropWindow : TenMicaBackdropWindowT<TenMicaBackdropWindow, implementation::TenMicaBackdropWindow>
    {
    };
}
