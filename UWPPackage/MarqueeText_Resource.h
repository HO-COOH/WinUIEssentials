#pragma once

#include "MarqueeText_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct MarqueeText_Resource : MarqueeText_ResourceT<MarqueeText_Resource>
    {
        MarqueeText_Resource() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct MarqueeText_Resource : MarqueeText_ResourceT<MarqueeText_Resource, implementation::MarqueeText_Resource>
    {
    };
}
