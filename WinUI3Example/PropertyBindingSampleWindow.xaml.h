#pragma once

#include "PropertyBindingSampleWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct PropertyBindingSampleWindow : PropertyBindingSampleWindowT<PropertyBindingSampleWindow>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct PropertyBindingSampleWindow : PropertyBindingSampleWindowT<PropertyBindingSampleWindow, implementation::PropertyBindingSampleWindow>
    {
    };
}
