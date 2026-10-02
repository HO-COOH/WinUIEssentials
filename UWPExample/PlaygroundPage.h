#pragma once

#include "PlaygroundPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct PlaygroundPage : PlaygroundPageT<PlaygroundPage>
    {
        void InitializeComponent();
        winrt::fire_and_forget LoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct PlaygroundPage : PlaygroundPageT<PlaygroundPage, implementation::PlaygroundPage>
    {
    };
}
