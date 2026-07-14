#pragma once

#include "SegmentedPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SegmentedPage : SegmentedPageT<SegmentedPage, implementation::SegmentedPage>
    {
    };
}
