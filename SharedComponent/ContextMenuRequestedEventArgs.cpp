#include "pch.h"
#include "ContextMenuRequestedEventArgs.h"
#if __has_include("ContextMenuRequestedEventArgs.g.cpp")
#include "ContextMenuRequestedEventArgs.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	ContextMenuRequestedEventArgs::ContextMenuRequestedEventArgs(
		int rowIndex, 
		int columnIndex, 
		winrt::Windows::Foundation::IInspectable const& dataContext
	) : m_rowIndex{ rowIndex }, m_columnIndex{ columnIndex }, m_dataContext{ dataContext }
	{
	}

	winrt::Windows::Foundation::IInspectable ContextMenuRequestedEventArgs::DataContext()
	{
		return m_dataContext;
	}

	winrt::WinUINamespace::UI::Xaml::Controls::MenuFlyout ContextMenuRequestedEventArgs::ContextMenu()
	{
		return m_contextMenu;
	}

	void ContextMenuRequestedEventArgs::ContextMenu(winrt::WinUINamespace::UI::Xaml::Controls::MenuFlyout const& value)
	{
		m_contextMenu = value;
		m_handled = true;
	}
}
