#pragma once

#include "EssentialWindowWithMenu.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct EssentialWindowWithMenu : EssentialWindowWithMenuT<EssentialWindowWithMenu>
    {
        EssentialWindowWithMenu()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct EssentialWindowWithMenu : EssentialWindowWithMenuT<EssentialWindowWithMenu, implementation::EssentialWindowWithMenu>
    {
    };
}
