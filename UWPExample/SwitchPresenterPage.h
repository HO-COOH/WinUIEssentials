#pragma once

#include "SwitchPresenterPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SwitchPresenterPage : SwitchPresenterPageT<SwitchPresenterPage>
    {
        SwitchPresenterPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SwitchPresenterPage : SwitchPresenterPageT<SwitchPresenterPage, implementation::SwitchPresenterPage>
    {
    };
}
