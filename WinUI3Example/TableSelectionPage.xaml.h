#pragma once

#include "TableSelectionPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TableSelectionPage : TableSelectionPageT<TableSelectionPage>
    {
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TableSelectionPage : TableSelectionPageT<TableSelectionPage, implementation::TableSelectionPage>
    {
    };
}
