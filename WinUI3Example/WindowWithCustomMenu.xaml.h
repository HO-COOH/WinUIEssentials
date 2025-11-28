#pragma once

#include "WindowWithCustomMenu.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowWithCustomMenu : WindowWithCustomMenuT<WindowWithCustomMenu>
    {
        WindowWithCustomMenu()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WindowWithCustomMenu : WindowWithCustomMenuT<WindowWithCustomMenu, implementation::WindowWithCustomMenu>
    {
    };
}
