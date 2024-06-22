#pragma once

#include "Placeholder.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct Placeholder : PlaceholderT<Placeholder>
    {
        Placeholder() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Placeholder : PlaceholderT<Placeholder, implementation::Placeholder>
    {
    };
}
