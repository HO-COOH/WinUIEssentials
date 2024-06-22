#pragma once

#include "BadgePage.g.h"

namespace winrt::UWPExample::implementation
{
    struct BadgePage : BadgePageT<BadgePage>
    {
        BadgePage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct BadgePage : BadgePageT<BadgePage, implementation::BadgePage>
    {
    };
}
