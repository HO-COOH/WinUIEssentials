#pragma once

#include "TransparentWindowDemo.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TransparentWindowDemo : TransparentWindowDemoT<TransparentWindowDemo>
    {
        TransparentWindowDemo() = default;

    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TransparentWindowDemo : TransparentWindowDemoT<TransparentWindowDemo, implementation::TransparentWindowDemo>
    {
    };
}
