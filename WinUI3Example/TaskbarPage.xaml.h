// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "TaskbarPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TaskbarPage : TaskbarPageT<TaskbarPage>
    {
        TaskbarPage();
        void ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TaskbarPage : TaskbarPageT<TaskbarPage, implementation::TaskbarPage>
    {
    };
}
