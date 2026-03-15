#pragma once

#include "MicaBackdropsPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct MicaBackdropsPage : MicaBackdropsPageT<MicaBackdropsPage>
    {
        MicaBackdropsPage() = default;

        void CreateMicaButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateDefaultMicaButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateStandardMicaButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateMicaWithFallbackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct MicaBackdropsPage : MicaBackdropsPageT<MicaBackdropsPage, implementation::MicaBackdropsPage>
    {
    };
}
