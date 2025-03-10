#pragma once

#include "ExtensionsPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ExtensionsPage : ExtensionsPageT<ExtensionsPage>
    {
        ExtensionsPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void SuccessLoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void FailedLoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ExtensionsPage : ExtensionsPageT<ExtensionsPage, implementation::ExtensionsPage>
    {
    };
}
