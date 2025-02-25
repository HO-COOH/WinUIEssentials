#pragma once

#include "FlyoutWindow.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct FlyoutWindow : FlyoutWindowT<FlyoutWindow>
    {
        FlyoutWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct FlyoutWindow : FlyoutWindowT<FlyoutWindow, implementation::FlyoutWindow>
    {
    };
}
