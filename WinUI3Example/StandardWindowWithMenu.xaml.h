#pragma once

#include "StandardWindowWithMenu.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct StandardWindowWithMenu : StandardWindowWithMenuT<StandardWindowWithMenu>
    {
        StandardWindowWithMenu()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct StandardWindowWithMenu : StandardWindowWithMenuT<StandardWindowWithMenu, implementation::StandardWindowWithMenu>
    {
    };
}
