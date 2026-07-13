#pragma once

#include "SliderHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SliderHelperPage : SliderHelperPageT<SliderHelperPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SliderHelperPage : SliderHelperPageT<SliderHelperPage, implementation::SliderHelperPage>
    {
    };
}
