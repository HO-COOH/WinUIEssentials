#pragma once

#include "UIElementExtensionPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct UIElementExtensionPage : UIElementExtensionPageT<UIElementExtensionPage>
    {
        UIElementExtensionPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct UIElementExtensionPage : UIElementExtensionPageT<UIElementExtensionPage, implementation::UIElementExtensionPage>
    {
    };
}
