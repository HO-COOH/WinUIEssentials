#include "pch.h"
#include "TableCellDataWrapper.h"
#if __has_include("TableCellDataWrapper.g.cpp")
#include "TableCellDataWrapper.g.cpp"
#endif
#include "Table.h"

namespace winrt::PackageRoot::implementation
{
    TableCellDataWrapper::TableCellDataWrapper(Table& table, int row, int column, winrt::Windows::Foundation::IInspectable const& value) :
		m_table_ref(table),
		m_row(row),
		m_column(column),
		m_value(value)
    {
    }
    
    winrt::Windows::Foundation::IInspectable TableCellDataWrapper::Value()
    {
        return m_value;
    }
    
    void TableCellDataWrapper::Value(winrt::Windows::Foundation::IInspectable const& value)
    {
        if (value == m_value)
            return;

        m_value = value;
		m_table_ref.m_tableData.SetData(m_row, m_column, value);
        raisePropertyChange(L"Value");
    }
}
