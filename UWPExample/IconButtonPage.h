#pragma once

#include "IconButtonPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct IconButtonPage : IconButtonPageT<IconButtonPage>
    {
        IconButtonPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void NormalInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ToggleInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct IconButtonPage : IconButtonPageT<IconButtonPage, implementation::IconButtonPage>
    {
    };
}
