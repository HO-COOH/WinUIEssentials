#include "pch.h"
#include "CodeWindow.xaml.h"
#if __has_include("CodeWindow.g.cpp")
#include "CodeWindow.g.cpp"
#endif


namespace winrt::WinUI3Example::implementation
{
	CodeWindow::CodeWindow(winrt::hstring const& title, winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& codeItems)
		: m_title{title}
		, m_codeItems{codeItems}
	{
		ExtendsContentIntoTitleBar(true);
	}

	winrt::hstring CodeWindow::WindowTitle()
	{
		return m_title;
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> CodeWindow::CodeItems()
	{
		return m_codeItems;
	}
}
