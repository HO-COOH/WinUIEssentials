#pragma once

#include "MarqueeContainerPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct MarqueeContainerPage : MarqueeContainerPageT<MarqueeContainerPage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct MarqueeContainerPage : MarqueeContainerPageT<MarqueeContainerPage, implementation::MarqueeContainerPage>
    {
    };
}
