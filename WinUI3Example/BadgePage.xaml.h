// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "BadgePage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct BadgePage : BadgePageT<BadgePage>
    {
        BadgePage() = default;

        void ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct BadgePage : BadgePageT<BadgePage, implementation::BadgePage>
    {
    };
}
