#pragma once

#include "TableConextMenuPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TableConextMenuPage : TableConextMenuPageT<TableConextMenuPage>
    {

        void OnTableContextMenuRequested(
            winrt::WinUI3Package::Table const& sender,
            winrt::WinUI3Package::ContextMenuRequestedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TableConextMenuPage : TableConextMenuPageT<TableConextMenuPage, implementation::TableConextMenuPage>
    {
    };
}
