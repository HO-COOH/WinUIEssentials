#pragma once

#include "ContentDialogContent_Resource.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ContentDialogContent_Resource : ContentDialogContent_ResourceT<ContentDialogContent_Resource>
    {
        ContentDialogContent_Resource() = default;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ContentDialogContent_Resource : ContentDialogContent_ResourceT<ContentDialogContent_Resource, implementation::ContentDialogContent_Resource>
    {
    };
}
