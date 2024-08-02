#pragma once

#include "TaskbarIconSource.g.h"
#include <functional>

namespace winrt::WinUI3Example::implementation
{
    struct TaskbarIconSource : TaskbarIconSourceT<TaskbarIconSource>
    {
        TaskbarIconSource() = default;
        winrt::Windows::Foundation::IAsyncAction Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        std::function<void(winrt::Windows::Foundation::Uri)> onIconSet;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TaskbarIconSource : TaskbarIconSourceT<TaskbarIconSource, implementation::TaskbarIconSource>
    {
    };
}
