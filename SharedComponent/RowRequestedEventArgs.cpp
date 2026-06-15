#include "pch.h"
#include "RowRequestedEventArgs.h"
#if __has_include("RowRequestedEventArgs.g.cpp")
#include "RowRequestedEventArgs.g.cpp"
#endif
//#include "TextLayoutCache.h"
//#include "TableOverlayManager.h"
#include "Table.h"

namespace winrt::PackageRoot::implementation
{
	RowRequestedEventArgs::RowRequestedEventArgs(int startRow, int endRow, Table& table) :
		m_startRow{ startRow }, m_endRow{ endRow }, m_table{ table }
	{
		m_setRowData.reserve(table.m_columns->Size());
	}

	int RowRequestedEventArgs::StartRow()
	{
		return m_startRow;
	}

	int RowRequestedEventArgs::EndRow()
	{
		return m_endRow;
	}

	void RowRequestedEventArgs::SetRow(int row, winrt::array_view<winrt::Windows::Foundation::IInspectable const> const& content)
	{
		for (uint32_t col = 0; col < content.size(); ++col)
		{
			auto const& cell = content[col];
			if (auto str = cell.try_as<winrt::hstring>())
				m_table.m_d2dContent.m_textLayoutCache.SetCellContent(row, static_cast<int>(col), std::wstring_view{ *str });
			else
				m_setRowData.push_back(SetRowData{ row, static_cast<int>(col), cell });
		}

		if (!m_setRowData.empty())
		{
			m_table.m_d2dContent.m_dispatcher.TryEnqueue([setRowData = std::move(m_setRowData), &overlayManager = m_table.m_overlayManager]()
			{
				for (auto const& data : setRowData)
					overlayManager.SetCellContent(data.row, data.col, data.content);
			});
		}
		m_table.m_d2dContent.m_textLayoutCache.MarkRowFresh(row);
	}

	bool RowRequestedEventArgs::IsCanceled()
	{
		return false;
	}

	winrt::event_token RowRequestedEventArgs::Canceled(winrt::Windows::Foundation::EventHandler<winrt::PackageRoot::RowRequestedEventArgs> const& handler)
	{
		return m_canceled.add(handler);
	}

	void RowRequestedEventArgs::Canceled(winrt::event_token const& token)
	{
		m_canceled.remove(token);
	}
}
