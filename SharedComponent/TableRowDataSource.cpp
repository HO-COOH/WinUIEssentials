#include "pch.h"
#include "TableRowDataSource.h"
#include <algorithm>
#include <string>
#include <vector>
#include "TableRow.h"

namespace winrt::PackageRoot::implementation
{
    TableRowDataSource::TableRowDataSource()
    {
        m_items = winrt::single_threaded_vector<winrt::PackageRoot::TableRow>();
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow> TableRowDataSource::Items()
    {
        return m_items;
    }

    void TableRowDataSource::Changed(ChangedCallback callback)
    {
        m_changed = std::move(callback);
    }

    void TableRowDataSource::notifyChanged(int32_t startRow, int32_t endRow)
    {
        if (endRow >= startRow)
            m_updateRowData(*this, winrt::PackageRoot::UpdateRowDataEventArgs{ startRow, endRow });

        if (m_changed)
            m_changed(startRow, endRow);
    }

    int32_t TableRowDataSource::RowCount()
    {
        return static_cast<int32_t>(m_items.Size());
    }

    int32_t TableRowDataSource::RowRequested(winrt::PackageRoot::RowRequestedEventArgs const& args)
    {
        if (m_items.Size() == 0)
            return 0;

        int32_t const start = args.StartRow();
        int32_t const end = (std::min)(args.EndRow(), static_cast<int32_t>(m_items.Size()) - 1);
        if (end < start)
            return 0;

        std::vector<winrt::Windows::Foundation::IInspectable> cells;
        for (int32_t row = start; row <= end; ++row)
        {
            auto const rowItems = m_items.GetAt(row);
            args.SetRow(row, winrt::get_self<TableRow>(rowItems)->m_data);
        }
        return end - start + 1;
    }

    void TableRowDataSource::SetData(int32_t row, int32_t column, winrt::Windows::Foundation::IInspectable const& value)
    {
        if (row < 0 || column < 0 || row >= m_items.Size())
            return;

        bool changed = false;

        auto const rowItems = m_items.GetAt(row);
        if (rowItems.GetAt(column) != value)
        {
            rowItems.SetAt(column, value);
            changed = true;
        }

        if (changed)
            notifyChanged(row, row);
    }

    winrt::event_token TableRowDataSource::UpdateRowData(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::UpdateRowDataEventArgs> const& handler)
    {
        return m_updateRowData.add(handler);
    }

    void TableRowDataSource::UpdateRowData(winrt::event_token const& token) noexcept
    {
        m_updateRowData.remove(token);
    }
}
