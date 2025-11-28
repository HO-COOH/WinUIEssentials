#pragma once

#include "IncrementalLoadingPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct IncrementalLoadingPage : IncrementalLoadingPageT<IncrementalLoadingPage>
    {
        IncrementalLoadingPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        //WinUI3Example::IIncrementLoadingVector Persons();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct IncrementalLoadingPage : IncrementalLoadingPageT<IncrementalLoadingPage, implementation::IncrementalLoadingPage>
    {
    };
}
