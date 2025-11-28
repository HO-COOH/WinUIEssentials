#pragma once

#include "SampleThemeListener.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SampleThemeListener : SampleThemeListenerT<SampleThemeListener>
    {
        SampleThemeListener() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SampleThemeListener : SampleThemeListenerT<SampleThemeListener, implementation::SampleThemeListener>
    {
    };
}
