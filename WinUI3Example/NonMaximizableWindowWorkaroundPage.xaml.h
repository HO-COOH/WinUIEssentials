#pragma once

#include "NonMaximizableWindowWorkaroundPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct NonMaximizableWindowWorkaroundPage : NonMaximizableWindowWorkaroundPageT<NonMaximizableWindowWorkaroundPage>
    {
        void NormalButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void WorkaroundButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct NonMaximizableWindowWorkaroundPage : NonMaximizableWindowWorkaroundPageT<NonMaximizableWindowWorkaroundPage, implementation::NonMaximizableWindowWorkaroundPage>
    {
    };
}
