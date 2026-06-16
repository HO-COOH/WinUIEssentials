#pragma once

#include "SamplePage4.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SamplePage4 : SamplePage4T<SamplePage4>
    {
        SamplePage4() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SamplePage4 : SamplePage4T<SamplePage4, implementation::SamplePage4>
    {
    };
}
