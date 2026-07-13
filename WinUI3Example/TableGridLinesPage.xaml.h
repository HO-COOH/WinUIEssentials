#pragma once

#include "TableGridLinesPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TableGridLinesPage : TableGridLinesPageT<TableGridLinesPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TableGridLinesPage : TableGridLinesPageT<TableGridLinesPage, implementation::TableGridLinesPage>
    {
    };
}
