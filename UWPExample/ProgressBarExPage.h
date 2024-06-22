#pragma once

#include "ProgressBarExPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ProgressBarExPage : ProgressBarExPageT<ProgressBarExPage>
    {
        ProgressBarExPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ProgressBarExPage : ProgressBarExPageT<ProgressBarExPage, implementation::ProgressBarExPage>
    {
    };
}
