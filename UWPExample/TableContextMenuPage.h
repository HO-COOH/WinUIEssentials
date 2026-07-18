#pragma once

#include "TableContextMenuPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct TableContextMenuPage : TableContextMenuPageT<TableContextMenuPage>
    {
        void OnTableContextMenuRequested(
            winrt::UWPPackage::Table const& sender,
            winrt::UWPPackage::ContextMenuRequestedEventArgs const& args);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct TableContextMenuPage : TableContextMenuPageT<TableContextMenuPage, implementation::TableContextMenuPage>
    {
    };
}
