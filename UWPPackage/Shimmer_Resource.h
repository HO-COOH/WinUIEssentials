#pragma once

#include "Shimmer_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct Shimmer_Resource : Shimmer_ResourceT<Shimmer_Resource>
    {
        Shimmer_Resource() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct Shimmer_Resource : Shimmer_ResourceT<Shimmer_Resource, implementation::Shimmer_Resource>
    {
    };
}
