#pragma once

#include "SegmentedItem.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct SegmentedItem : SegmentedItemT<SegmentedItem>, TemplateControlHelper<SegmentedItem>
    {
        SegmentedItem() = default;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct SegmentedItem : SegmentedItemT<SegmentedItem, implementation::SegmentedItem>
    {
    };
}
