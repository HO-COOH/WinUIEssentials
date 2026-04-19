#pragma once

#include "AcrylicBackdropsPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct AcrylicBackdropsPage : AcrylicBackdropsPageT<AcrylicBackdropsPage>
    {
        AcrylicBackdropsPage() = default;
        void CreateAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateDefaultAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateStandardAcrylicButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct AcrylicBackdropsPage : AcrylicBackdropsPageT<AcrylicBackdropsPage, implementation::AcrylicBackdropsPage>
    {
    };
}
