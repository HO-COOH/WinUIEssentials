#pragma once

#include "SegmentedItem.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::PackageRoot::implementation
{
    struct SegmentedItem : SegmentedItemT<SegmentedItem>, TemplateControlHelper<SegmentedItem, false>
    {
        SegmentedItem() = default;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SegmentedItem : SegmentedItemT<SegmentedItem, implementation::SegmentedItem>
    {
    };
}
