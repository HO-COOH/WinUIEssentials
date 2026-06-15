#pragma once

#include "TableRow.h"
#include <functional>

namespace winrt::PackageRoot::implementation
{
    struct TableRowDataSource : winrt::implements<TableRowDataSource, winrt::PackageRoot::ITableData>
    {
        using ChangedCallback = std::function<void(int32_t startRow, int32_t endRow)>;

        TableRowDataSource();

        winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow> Items();
        void Changed(ChangedCallback callback);

        int32_t RowCount();
        int32_t RowRequested(winrt::PackageRoot::RowRequestedEventArgs const& args);
        void SetData(int32_t row, int32_t column, winrt::Windows::Foundation::IInspectable const& value);

        winrt::event_token UpdateRowData(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::UpdateRowDataEventArgs> const& handler);
        void UpdateRowData(winrt::event_token const& token) noexcept;

    private:
        void notifyChanged(int32_t startRow, int32_t endRow);

        winrt::Windows::Foundation::Collections::IVector<winrt::PackageRoot::TableRow> m_items{ nullptr };
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::UpdateRowDataEventArgs>> m_updateRowData;
        ChangedCallback m_changed;
    };
}
