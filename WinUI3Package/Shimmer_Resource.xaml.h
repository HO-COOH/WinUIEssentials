#pragma once

#include "Shimmer_Resource.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct Shimmer_Resource : Shimmer_ResourceT<Shimmer_Resource>
    {
        Shimmer_Resource() = default;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Shimmer_Resource : Shimmer_ResourceT<Shimmer_Resource, implementation::Shimmer_Resource>
    {
    };
}
