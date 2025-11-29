#pragma once

#include "DatePickerHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DatePickerHelperPage : DatePickerHelperPageT<DatePickerHelperPage>
    {
        DatePickerHelperPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DatePickerHelperPage : DatePickerHelperPageT<DatePickerHelperPage, implementation::DatePickerHelperPage>
    {
    };
}
