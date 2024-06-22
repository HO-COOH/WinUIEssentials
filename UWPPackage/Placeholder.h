#pragma once

#include "Placeholder.g.h"

namespace winrt::UWPPackage::implementation
{
    struct Placeholder : PlaceholderT<Placeholder>
    {
        Placeholder() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct Placeholder : PlaceholderT<Placeholder, implementation::Placeholder>
    {
    };
}
