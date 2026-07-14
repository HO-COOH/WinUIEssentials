#pragma once

#include "SamplePage3.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SamplePage3 : SamplePage3T<SamplePage3>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SamplePage3 : SamplePage3T<SamplePage3, implementation::SamplePage3>
    {
    };
}
