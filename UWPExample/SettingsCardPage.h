#pragma once

#include "SettingsCardPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SettingsCardPage : SettingsCardPageT<SettingsCardPage>
    {
        SettingsCardPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SettingsCardPage : SettingsCardPageT<SettingsCardPage, implementation::SettingsCardPage>
    {
    };
}
