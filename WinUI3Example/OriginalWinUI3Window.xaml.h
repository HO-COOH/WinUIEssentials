#pragma once

#include "OriginalWinUI3Window.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct OriginalWinUI3Window : OriginalWinUI3WindowT<OriginalWinUI3Window>
    {
        OriginalWinUI3Window()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct OriginalWinUI3Window : OriginalWinUI3WindowT<OriginalWinUI3Window, implementation::OriginalWinUI3Window>
    {
    };
}
