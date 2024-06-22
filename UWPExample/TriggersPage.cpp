#include "pch.h"
#include "TriggersPage.h"
#if __has_include("TriggersPage.g.cpp")
#include "TriggersPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{

	void TriggersPage::AddButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		if (OurList())
		{
			OurList().Items().Append(winrt::box_value(L"Item"));
		}
	}


	void TriggersPage::RemoveButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		if (OurList())
		{
			OurList().Items().RemoveAt(0);
		}
	}

}

