#pragma once

#include "CaptionButtonThemeWorkaroundPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CaptionButtonThemeWorkaroundPage : CaptionButtonThemeWorkaroundPageT<CaptionButtonThemeWorkaroundPage>
    {
        CaptionButtonThemeWorkaroundPage() = default;

        void CreateDefaultWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateWorkaroundWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CompareWindowsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CaptionButtonThemeWorkaroundPage : CaptionButtonThemeWorkaroundPageT<CaptionButtonThemeWorkaroundPage, implementation::CaptionButtonThemeWorkaroundPage>
    {
    };
}
