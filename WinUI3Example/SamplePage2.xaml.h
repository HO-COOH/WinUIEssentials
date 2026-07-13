#pragma once

#include "SamplePage2.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SamplePage2 : SamplePage2T<SamplePage2>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SamplePage2 : SamplePage2T<SamplePage2, implementation::SamplePage2>
    {
    };
}
