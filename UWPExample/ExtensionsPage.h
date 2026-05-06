#pragma once

#include "ExtensionsPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct ExtensionsPage : ExtensionsPageT<ExtensionsPage>
    {
        ExtensionsPage() = default;

        void SuccessLoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void FailedLoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct ExtensionsPage : ExtensionsPageT<ExtensionsPage, implementation::ExtensionsPage>
    {
    };
}
