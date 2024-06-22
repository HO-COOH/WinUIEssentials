#pragma once

#include "DependentValuePage.g.h"

namespace winrt::UWPExample::implementation
{
    struct DependentValuePage : DependentValuePageT<DependentValuePage>
    {
        DependentValuePage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct DependentValuePage : DependentValuePageT<DependentValuePage, implementation::DependentValuePage>
    {
    };
}
