#pragma once

#include "TableAlternateRowColorsPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TableAlternateRowColorsPage : TableAlternateRowColorsPageT<TableAlternateRowColorsPage>
    {
        TableAlternateRowColorsPage() = default;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TableAlternateRowColorsPage : TableAlternateRowColorsPageT<TableAlternateRowColorsPage, implementation::TableAlternateRowColorsPage>
    {
    };
}
