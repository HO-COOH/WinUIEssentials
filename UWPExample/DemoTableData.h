#pragma once

#include "DemoTableData.g.h"
#include "TableTestData.hpp"
#include <ITableDataBase.hpp>

namespace winrt::UWPExample::implementation
{
    struct DemoTableData : DemoTableDataT<DemoTableData>, ITableDataBase<DemoTableData>
    {

        int RowCount();
        int RowRequested(winrt::UWPPackage::RowRequestedEventArgs const& args);
        void SetData(int row, int column, winrt::Windows::Foundation::IInspectable const& value);
    private:
        TableTestData m_data;
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct DemoTableData : DemoTableDataT<DemoTableData, implementation::DemoTableData>
    {
    };
}
