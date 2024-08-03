#pragma once

#include "TaskbarIconPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TaskbarIconPage : TaskbarIconPageT<TaskbarIconPage>
    {
        TaskbarIconPage();
        void NormalIconAdd_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void NormalIconRemove_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ThemeAdaptiveIconAddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void ThemeAdaptiveIconRemoveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RadioButtons_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TaskbarIconPage : TaskbarIconPageT<TaskbarIconPage, implementation::TaskbarIconPage>
    {
    };
}
