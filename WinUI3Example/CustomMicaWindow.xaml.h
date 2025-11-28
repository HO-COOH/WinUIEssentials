#pragma once

#include "CustomMicaWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CustomMicaWindow : CustomMicaWindowT<CustomMicaWindow>
    {
        CustomMicaWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CustomMicaWindow : CustomMicaWindowT<CustomMicaWindow, implementation::CustomMicaWindow>
    {
    };
}
