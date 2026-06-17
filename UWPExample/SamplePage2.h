#pragma once

#include "SamplePage2.g.h"

namespace winrt::UWPExample::implementation
{
    struct SamplePage2 : SamplePage2T<SamplePage2>
    {
        SamplePage2() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SamplePage2 : SamplePage2T<SamplePage2, implementation::SamplePage2>
    {
    };
}
