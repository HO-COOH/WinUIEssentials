#pragma once

#include "Segmented_Resource.g.h"

namespace winrt::UWPPackage::implementation
{
    struct Segmented_Resource : Segmented_ResourceT<Segmented_Resource>
    {
        Segmented_Resource() = default;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct Segmented_Resource : Segmented_ResourceT<Segmented_Resource, implementation::Segmented_Resource>
    {
    };
}
