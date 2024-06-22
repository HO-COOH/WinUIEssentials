#pragma once

#include "CursorControllerPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct CursorControllerPage : CursorControllerPageT<CursorControllerPage>
    {
        CursorControllerPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct CursorControllerPage : CursorControllerPageT<CursorControllerPage, implementation::CursorControllerPage>
    {
    };
}
