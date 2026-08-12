#pragma once

#include "TriggersPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TriggersPage : TriggersPageT<TriggersPage>
    {
        void AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void RemoveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TriggersPage : TriggersPageT<TriggersPage, implementation::TriggersPage>
    {
    };
}
