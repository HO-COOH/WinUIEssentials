#pragma once

#include "GroupBoxPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage>
    {
        GroupBoxPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct GroupBoxPage : GroupBoxPageT<GroupBoxPage, implementation::GroupBoxPage>
    {
    };
}
