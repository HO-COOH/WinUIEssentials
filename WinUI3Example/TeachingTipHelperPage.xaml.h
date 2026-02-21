#pragma once

#include "TeachingTipHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TeachingTipHelperPage : TeachingTipHelperPageT<TeachingTipHelperPage>
    {
        TeachingTipHelperPage() = default;
        void TestButton1_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TeachingTipHelperPage : TeachingTipHelperPageT<TeachingTipHelperPage, implementation::TeachingTipHelperPage>
    {
    };
}
