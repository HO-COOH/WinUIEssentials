#include "pch.h"
#include "DefaultTableContextMenu.h"
#if __has_include("DefaultTableContextMenu.g.cpp")
#include "DefaultTableContextMenu.g.cpp"
#endif
#include "Table.h"
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <string>

static void copyToClipboard(auto&& content)
{
	winrt::Windows::ApplicationModel::DataTransfer::DataPackage package;
	package.SetText(winrt::hstring{ content });
	winrt::Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(package);
}

namespace winrt::PackageRoot::implementation
{
	DefaultTableContextMenu::DefaultTableContextMenu(Table* table, int row, int column)
		: m_table(table), m_row(row), m_column(column)
	{
	}

	void DefaultTableContextMenu::CopyCell_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
	{
		//The text cache is source-indexed; map the display row through the sort order.
		auto const sourceRow = m_table->m_sortContext.Source(m_row);
		copyToClipboard(m_table->m_d2dContent.m_textLayoutCache.GetCellContent(sourceRow, m_column));
	}

	void DefaultTableContextMenu::CopyRow_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const&)
	{
		auto const sourceRow = m_table->m_sortContext.Source(m_row);
		auto const numColumns = static_cast<int>(m_table->m_d2dContent.m_columnWidthManager.NumColumns());
		std::wstring row;
		for (int c = 0; c < numColumns; ++c)
		{
			if (c > 0)
				row.push_back(L' ');
			row.append(m_table->m_d2dContent.m_textLayoutCache.GetCellContent(sourceRow, c));
		}

		copyToClipboard(std::move(row));
	}
}
