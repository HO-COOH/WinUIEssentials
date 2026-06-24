#pragma once

#include "TableAlternateRowColorsPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TableAlternateRowColorsPage : TableAlternateRowColorsPageT<TableAlternateRowColorsPage>
    {
        TableAlternateRowColorsPage() = default;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TableAlternateRowColorsPage : TableAlternateRowColorsPageT<TableAlternateRowColorsPage, implementation::TableAlternateRowColorsPage>
    {
    };
}
