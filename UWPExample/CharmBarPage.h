#pragma once

#include "CharmBarPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct CharmBarPage : CharmBarPageT<CharmBarPage>
    {
        CharmBarPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void LocalSettingsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void GlobalSettingsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct CharmBarPage : CharmBarPageT<CharmBarPage, implementation::CharmBarPage>
    {
    };
}
