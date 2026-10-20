#pragma once

#include "NumberBoxHelperPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct NumberBoxHelperPage : NumberBoxHelperPageT<NumberBoxHelperPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct NumberBoxHelperPage : NumberBoxHelperPageT<NumberBoxHelperPage, implementation::NumberBoxHelperPage>
    {
    };
}
