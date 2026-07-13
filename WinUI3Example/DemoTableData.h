#pragma once

#include "DemoTableData.g.h"
#include "TableTestData.hpp"
#include <ITableDataBase.hpp>

namespace winrt::WinUI3Example::implementation
{
	struct DemoTableData : DemoTableDataT<DemoTableData>, ITableDataBase<DemoTableData>
    {

        int RowCount();
        int RowRequested(winrt::WinUI3Package::RowRequestedEventArgs const& args);
        void SetData(int row, int column, winrt::Windows::Foundation::IInspectable const& value);
    private:
        TableTestData m_data;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DemoTableData : DemoTableDataT<DemoTableData, implementation::DemoTableData>
    {
    };
}
