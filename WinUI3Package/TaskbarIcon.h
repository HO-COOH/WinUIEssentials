#pragma once

#include "TaskbarIcon.g.h"
#include <shellapi.h>

namespace winrt::WinUI3Package::implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon>
    {
        TaskbarIcon()
        {
            OutputDebugString(L"Constructed\n");
        }

        WinUI3Package::GeneratedIconSource IconSource();
        void IconSource(WinUI3Package::GeneratedIconSource value);

    private:
        WinUI3Package::GeneratedIconSource m_iconSource{ nullptr };

        NOTIFYICONDATA nid;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TaskbarIcon : TaskbarIconT<TaskbarIcon, implementation::TaskbarIcon>
    {
    };
}
