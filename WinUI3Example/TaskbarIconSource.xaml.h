#pragma once

#include "TaskbarIconSource.g.h"
#include <functional>
#include <PropertyChangeHelper.hpp>

namespace winrt::WinUI3Example::implementation
{
    struct TaskbarIconSource : TaskbarIconSourceT<TaskbarIconSource>, MvvmHelper::PropertyChangeHelper<TaskbarIconSource>
    {
        TaskbarIconSource() = default;
        winrt::Windows::Foundation::IAsyncAction Button_Click(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        
        winrt::hstring IconFile;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TaskbarIconSource : TaskbarIconSourceT<TaskbarIconSource, implementation::TaskbarIconSource>
    {
    };
}
