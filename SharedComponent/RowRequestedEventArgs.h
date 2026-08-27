#pragma once

#include "RowRequestedEventArgs.g.h"

class TextLayoutCache;
class TableOverlayManager;

namespace winrt::PackageRoot::implementation
{
    struct Table;
    struct RowRequestedEventArgs : RowRequestedEventArgsT<RowRequestedEventArgs>
    {
		RowRequestedEventArgs(int startRow, int endRow, Table& table);

        int StartRow();
        int EndRow();
        void SetRow(int row, winrt::array_view<winrt::Windows::Foundation::IInspectable const> const& content);
    private:
        int m_startRow{};
        int m_endRow{};
		Table& m_table;
        
        struct SetRowData
        {
            int row;
            int col;
            winrt::Windows::Foundation::IInspectable content;
        };

		std::vector<SetRowData> m_setRowData; //cache for SetRow calls so that we call dispatcherQueue only once per SetRow() call
    };
}

