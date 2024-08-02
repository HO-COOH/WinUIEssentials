#pragma once

#include "TaskbarIconPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TaskbarIconPage : TaskbarIconPageT<TaskbarIconPage>
    {
        TaskbarIconPage();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TaskbarIconPage : TaskbarIconPageT<TaskbarIconPage, implementation::TaskbarIconPage>
    {
    };
}
