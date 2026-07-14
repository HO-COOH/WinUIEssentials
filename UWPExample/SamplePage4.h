#pragma once

#include "SamplePage4.g.h"

namespace winrt::UWPExample::implementation
{
    struct SamplePage4 : SamplePage4T<SamplePage4>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SamplePage4 : SamplePage4T<SamplePage4, implementation::SamplePage4>
    {
    };
}
