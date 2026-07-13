#pragma once

#include "SamplePage3.g.h"

namespace winrt::UWPExample::implementation
{
    struct SamplePage3 : SamplePage3T<SamplePage3>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SamplePage3 : SamplePage3T<SamplePage3, implementation::SamplePage3>
    {
    };
}
