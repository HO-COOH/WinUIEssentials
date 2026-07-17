#include "pch.h"
#include "DefaultTableHeaderContextMenu.h"
#if __has_include("DefaultTableHeaderContextMenu.g.cpp")
#include "DefaultTableHeaderContextMenu.g.cpp"
#endif
#include "TableSortContext.hpp"
#include "Table.h"

namespace winrt::PackageRoot::implementation
{
	DefaultTableHeaderContextMenu::DefaultTableHeaderContextMenu(Table* table, int columnIndex) : 
		m_columnIndex{ columnIndex }, m_table{ table }
	{
	}

	void DefaultTableHeaderContextMenu::InitializeComponent()
	{
		DefaultTableHeaderContextMenuT::InitializeComponent();
		for (auto const& item : Items())
			item.DataContext(*this);
	}

	bool DefaultTableHeaderContextMenu::IsSortAscendingEnabled()
	{
		return isSortable() && m_table->m_sortContext.sortParameter.sortDirection != TableSortDirection::Ascending;
	}

	bool DefaultTableHeaderContextMenu::IsSortDescendingEnabled()
	{
		return isSortable() && m_table->m_sortContext.sortParameter.sortDirection != TableSortDirection::Descending;
	}

	bool DefaultTableHeaderContextMenu::IsClearSortEnabled()
	{
		return m_table->m_sortContext.sortParameter;
	}

	void DefaultTableHeaderContextMenu::SortAscend_Click(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{
		m_table->SetSort({ .sortColumn = m_columnIndex, .sortDirection = TableSortDirection::Ascending });
	}

	void DefaultTableHeaderContextMenu::SortDescend_Click(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{
		m_table->SetSort({ .sortColumn = m_columnIndex, .sortDirection = TableSortDirection::Descending });
	}

	void DefaultTableHeaderContextMenu::ClearSorting_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{
		m_table->SetSort({ .sortColumn = -1, .sortDirection = TableSortDirection::None });
	}

	bool DefaultTableHeaderContextMenu::isSortable() const
	{
		return m_table->m_columns->m_data[m_columnIndex]->SortEnabled() && m_table->m_d2dContent.m_textLayoutCache.RowCount() > 0;
	}
}
