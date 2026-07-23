#pragma once

#include "WindowCaptionButtonThemeWorkaroundPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct WindowCaptionButtonThemeWorkaroundPage : WindowCaptionButtonThemeWorkaroundPageT<WindowCaptionButtonThemeWorkaroundPage>
    {
        void CreateWorkaroundWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CompareWindowsButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void CreateDefaultWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct WindowCaptionButtonThemeWorkaroundPage : WindowCaptionButtonThemeWorkaroundPageT<WindowCaptionButtonThemeWorkaroundPage, implementation::WindowCaptionButtonThemeWorkaroundPage>
    {
    };
}
