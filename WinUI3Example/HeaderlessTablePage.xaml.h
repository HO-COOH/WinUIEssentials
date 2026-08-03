#pragma once

#include "HeaderlessTablePage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct HeaderlessTablePage : HeaderlessTablePageT<HeaderlessTablePage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct HeaderlessTablePage : HeaderlessTablePageT<HeaderlessTablePage, implementation::HeaderlessTablePage>
    {
    };
}
