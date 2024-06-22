#pragma once

#include "IconButtonPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct IconButtonPage : IconButtonPageT<IconButtonPage>
    {
        IconButtonPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void NormalInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ToggleInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct IconButtonPage : IconButtonPageT<IconButtonPage, implementation::IconButtonPage>
    {
    };
}
