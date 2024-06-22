#pragma once

#include "UIElementExtensionsPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct UIElementExtensionsPage : UIElementExtensionsPageT<UIElementExtensionsPage>
    {
        UIElementExtensionsPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct UIElementExtensionsPage : UIElementExtensionsPageT<UIElementExtensionsPage, implementation::UIElementExtensionsPage>
    {
    };
}
