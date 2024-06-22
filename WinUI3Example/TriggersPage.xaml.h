// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "TriggersPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TriggersPage : TriggersPageT<TriggersPage>
    {
        TriggersPage();
        void AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RemoveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TriggersPage : TriggersPageT<TriggersPage, implementation::TriggersPage>
    {
    };
}
