#pragma once

#include "AnimatedNumber_Resource.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct AnimatedNumber_Resource : AnimatedNumber_ResourceT<AnimatedNumber_Resource>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AnimatedNumber_Resource : AnimatedNumber_ResourceT<AnimatedNumber_Resource, implementation::AnimatedNumber_Resource>
    {
    };
}
