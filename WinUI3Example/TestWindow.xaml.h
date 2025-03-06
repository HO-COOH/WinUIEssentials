#pragma once

#include "TestWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TestWindow : TestWindowT<TestWindow>
    {
        TestWindow() = default;

    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TestWindow : TestWindowT<TestWindow, implementation::TestWindow>
    {
    };
}
