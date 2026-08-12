#include "pch.h"
#include "TriggersPage.h"
#if __has_include("TriggersPage.g.cpp")
#include "TriggersPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<TriggersPage> s_tags{ L"trigger", L"visualstate", L"visualstatemanager" };

	void TriggersPage::AddButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		OurList().Items().Append(winrt::box_value(L"Item"));
	}

	void TriggersPage::RemoveButton_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		OurList().Items().RemoveAt(0);
	}
}
