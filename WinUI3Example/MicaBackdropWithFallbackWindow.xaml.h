#pragma once

#include "MicaBackdropWithFallbackWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MicaBackdropWithFallbackWindow : MicaBackdropWithFallbackWindowT<MicaBackdropWithFallbackWindow>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MicaBackdropWithFallbackWindow : MicaBackdropWithFallbackWindowT<MicaBackdropWithFallbackWindow, implementation::MicaBackdropWithFallbackWindow>
    {
    };
}
