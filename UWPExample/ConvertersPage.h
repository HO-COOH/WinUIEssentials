#pragma once

#include "ConvertersPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ConvertersPage : ConvertersPageT<ConvertersPage>
    {
        ConvertersPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ConvertersPage : ConvertersPageT<ConvertersPage, implementation::ConvertersPage>
    {
    };
}
