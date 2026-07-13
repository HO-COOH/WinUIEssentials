#pragma once

#include "MarqueeText_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct MarqueeText_Resource : MarqueeText_ResourceT<MarqueeText_Resource>
    {
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct MarqueeText_Resource : MarqueeText_ResourceT<MarqueeText_Resource, implementation::MarqueeText_Resource>
    {
    };
}
