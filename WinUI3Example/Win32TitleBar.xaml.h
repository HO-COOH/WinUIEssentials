#pragma once

#include "Win32TitleBar.g.h"
#include <dwmapi.h>

namespace winrt::WinUI3Example::implementation
{
    struct Win32TitleBar : Win32TitleBarT<Win32TitleBar>
    {
        Win32TitleBar()
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
    struct Win32TitleBar : Win32TitleBarT<Win32TitleBar, implementation::Win32TitleBar>
    {
    };
}
