#pragma once

#include "HeaderlessTablePage.g.h"

namespace winrt::UWPExample::implementation
{
    struct HeaderlessTablePage : HeaderlessTablePageT<HeaderlessTablePage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct HeaderlessTablePage : HeaderlessTablePageT<HeaderlessTablePage, implementation::HeaderlessTablePage>
    {
    };
}
