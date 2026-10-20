#pragma once

#include "TeachingTipHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TeachingTipHelperPage : TeachingTipHelperPageT<TeachingTipHelperPage>
    {
        void TestButton1_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestButton2_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestButton3_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestButton4_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestButton5_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void TestButton6_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TeachingTipHelperPage : TeachingTipHelperPageT<TeachingTipHelperPage, implementation::TeachingTipHelperPage>
    {
    };
}
