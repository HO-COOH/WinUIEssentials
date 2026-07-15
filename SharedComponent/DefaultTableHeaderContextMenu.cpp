#include "pch.h"
#include "DefaultTableHeaderContextMenu.h"
#if __has_include("DefaultTableHeaderContextMenu.g.cpp")
#include "DefaultTableHeaderContextMenu.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	DefaultTableHeaderContextMenu::DefaultTableHeaderContextMenu(Table* table) : m_table(table)
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
		return false;
	}

	bool DefaultTableHeaderContextMenu::IsSortDescendingEnabled()
	{
		return true;
	}

	void DefaultTableHeaderContextMenu::SortAscend_Click(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{
	}

	void DefaultTableHeaderContextMenu::SortDescend_Click(
		winrt::Windows::Foundation::IInspectable const& sender,
		winrt::WinUINamespace::UI::Xaml::RoutedEventArgs const& e)
	{
	}
}
