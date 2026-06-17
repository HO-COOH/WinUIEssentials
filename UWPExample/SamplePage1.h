#pragma once

#include "SamplePage1.g.h"

namespace winrt::UWPExample::implementation
{
    struct SamplePage1 : SamplePage1T<SamplePage1>
    {
        SamplePage1() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SamplePage1 : SamplePage1T<SamplePage1, implementation::SamplePage1>
    {
    };
}
