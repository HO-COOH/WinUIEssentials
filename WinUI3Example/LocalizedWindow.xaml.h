#pragma once

#include "LocalizedWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct LocalizedWindow : LocalizedWindowT<LocalizedWindow>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct LocalizedWindow : LocalizedWindowT<LocalizedWindow, implementation::LocalizedWindow>
    {
    };
}
