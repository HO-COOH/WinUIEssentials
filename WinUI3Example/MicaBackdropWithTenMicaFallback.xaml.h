#pragma once

#include "MicaBackdropWithTenMicaFallback.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MicaBackdropWithTenMicaFallback : MicaBackdropWithTenMicaFallbackT<MicaBackdropWithTenMicaFallback>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MicaBackdropWithTenMicaFallback : MicaBackdropWithTenMicaFallbackT<MicaBackdropWithTenMicaFallback, implementation::MicaBackdropWithTenMicaFallback>
    {
    };
}
