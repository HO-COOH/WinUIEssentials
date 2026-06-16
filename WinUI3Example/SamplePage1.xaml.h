#pragma once

#include "SamplePage1.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SamplePage1 : SamplePage1T<SamplePage1>
    {
        SamplePage1() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SamplePage1 : SamplePage1T<SamplePage1, implementation::SamplePage1>
    {
    };
}
