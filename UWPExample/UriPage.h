#pragma once

#include "UriPage.g.h"


namespace winrt::UWPExample::implementation
{
    struct UriPage : UriPageT<UriPage>
    {
        UriPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Uris();
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct UriPage : UriPageT<UriPage, implementation::UriPage>
    {
    };
}
