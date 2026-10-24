#pragma once

#include "PlaygroundPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct PlaygroundPage : PlaygroundPageT<PlaygroundPage>
    {
        void InitializeComponent();
        void LoadButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    private:
        void showStatus(winrt::Microsoft::UI::Xaml::Controls::InfoBarSeverity severity, winrt::hstring const& title, winrt::hstring const& message);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct PlaygroundPage : PlaygroundPageT<PlaygroundPage, implementation::PlaygroundPage>
    {
    };
}
