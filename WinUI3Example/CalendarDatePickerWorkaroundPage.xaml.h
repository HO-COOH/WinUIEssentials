#pragma once

#include "CalendarDatePickerWorkaroundPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CalendarDatePickerWorkaroundPage : CalendarDatePickerWorkaroundPageT<CalendarDatePickerWorkaroundPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CalendarDatePickerWorkaroundPage : CalendarDatePickerWorkaroundPageT<CalendarDatePickerWorkaroundPage, implementation::CalendarDatePickerWorkaroundPage>
    {
    };
}
