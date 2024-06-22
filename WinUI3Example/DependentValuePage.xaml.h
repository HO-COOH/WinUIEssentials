// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "DependentValuePage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DependentValuePage : DependentValuePageT<DependentValuePage>
    {
        DependentValuePage() = default;

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DependentValuePage : DependentValuePageT<DependentValuePage, implementation::DependentValuePage>
    {
    };
}
