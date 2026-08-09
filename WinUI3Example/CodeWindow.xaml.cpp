#include "pch.h"
#include "CodeWindow.xaml.h"
#if __has_include("CodeWindow.g.cpp")
#include "CodeWindow.g.cpp"
#endif


namespace winrt::WinUI3Example::implementation
{
	CodeWindow::CodeWindow(winrt::hstring const& title, winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& codeItems)
		: m_codeItems{codeItems}
	{
		Title(title);
		ExtendsContentIntoTitleBar(true);
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> CodeWindow::CodeItems()
	{
		return m_codeItems;
	}
}
