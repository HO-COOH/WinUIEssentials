#pragma once

#include "TransparentWindowDemo.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TransparentWindowDemo : TransparentWindowDemoT<TransparentWindowDemo>
    {
        TransparentWindowDemo()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }


    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TransparentWindowDemo : TransparentWindowDemoT<TransparentWindowDemo, implementation::TransparentWindowDemo>
    {
    };
}
