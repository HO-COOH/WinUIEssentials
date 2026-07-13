#pragma once

#include "SegmentedPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage, implementation::SegmentedPage>
    {
    };
}
