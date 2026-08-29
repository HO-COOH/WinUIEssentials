#pragma once

#include "StringResourcePage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct StringResourcePage : StringResourcePageT<StringResourcePage>
    {
        void CreateDialogButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateWindowButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct StringResourcePage : StringResourcePageT<StringResourcePage, implementation::StringResourcePage>
    {
    };
}
