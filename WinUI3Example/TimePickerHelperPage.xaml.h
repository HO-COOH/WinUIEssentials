#pragma once

#include "TimePickerHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TimePickerHelperPage : TimePickerHelperPageT<TimePickerHelperPage>
    {
        TimePickerHelperPage() = default;

        static winrt::Windows::Foundation::TimeSpan CurrentTime();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TimePickerHelperPage : TimePickerHelperPageT<TimePickerHelperPage, implementation::TimePickerHelperPage>
    {
    };
}
