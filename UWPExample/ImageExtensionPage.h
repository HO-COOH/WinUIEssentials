#pragma once

#include "ImageExtensionPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ImageExtensionPage : ImageExtensionPageT<ImageExtensionPage>
    {
        ImageExtensionPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void SuccessLoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FailedLoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ImageExtensionPage : ImageExtensionPageT<ImageExtensionPage, implementation::ImageExtensionPage>
    {
    };
}
