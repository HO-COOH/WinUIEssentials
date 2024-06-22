#pragma once

#include "SegmentedItem.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::UWPPackage::implementation
{
    struct SegmentedItem : SegmentedItemT<SegmentedItem>, TemplateControlHelper<SegmentedItem>
    {
        SegmentedItem() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SegmentedItem : SegmentedItemT<SegmentedItem, implementation::SegmentedItem>
    {
    };
}
