#pragma once

#include "RowRequestedEventArgs.g.h"

namespace winrt::PackageRoot::implementation
{
    struct RowRequestedEventArgs : RowRequestedEventArgsT<RowRequestedEventArgs>
    {
        RowRequestedEventArgs() = default;

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct RowRequestedEventArgs : RowRequestedEventArgsT<RowRequestedEventArgs, implementation::RowRequestedEventArgs>
    {
    };
}
