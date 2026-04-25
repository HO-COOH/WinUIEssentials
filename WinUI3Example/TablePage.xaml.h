#pragma once

#include "TablePage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TablePage : TablePageT<TablePage>
    {
        TablePage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TablePage : TablePageT<TablePage, implementation::TablePage>
    {
    };
}
