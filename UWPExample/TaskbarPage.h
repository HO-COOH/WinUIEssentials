#pragma once

#include "TaskbarPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TaskbarPage : TaskbarPageT<TaskbarPage>
    {
        TaskbarPage() 
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TaskbarPage : TaskbarPageT<TaskbarPage, implementation::TaskbarPage>
    {
    };
}
