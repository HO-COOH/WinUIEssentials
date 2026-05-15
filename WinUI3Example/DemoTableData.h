#pragma once

#include "DemoTableData.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DemoTableData : DemoTableDataT<DemoTableData>
    {
        DemoTableData() = default;

        int RowCount();
        int RowRequested(winrt::WinUI3Package::RowRequestedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DemoTableData : DemoTableDataT<DemoTableData, implementation::DemoTableData>
    {
    };
}
