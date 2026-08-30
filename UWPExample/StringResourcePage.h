#pragma once

#include "StringResourcePage.g.h"

namespace winrt::UWPExample::implementation
{
    struct StringResourcePage : StringResourcePageT<StringResourcePage>
    {
        void CreateContentDialogButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct StringResourcePage : StringResourcePageT<StringResourcePage, implementation::StringResourcePage>
    {
    };
}
