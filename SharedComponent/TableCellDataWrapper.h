#pragma once

#include "TableCellDataWrapper.g.h"
#include <include/PropertyChangeHelper.hpp>

namespace winrt::PackageRoot::implementation
{
    struct Table;

	struct TableCellDataWrapper : TableCellDataWrapperT<TableCellDataWrapper>, MvvmHelper::PropertyChangeHelper<TableCellDataWrapper>
    {
        TableCellDataWrapper(Table& table, int row, int column, winrt::Windows::Foundation::IInspectable const& value);

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
    private:
		Table& m_table_ref;
        int m_row;
        int m_column;
		winrt::Windows::Foundation::IInspectable m_value;
    };
}
