#pragma once

#include "TableGridLinesPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TableGridLinesPage : TableGridLinesPageT<TableGridLinesPage>
    {
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TableGridLinesPage : TableGridLinesPageT<TableGridLinesPage, implementation::TableGridLinesPage>
    {
    };
}
