#include "pch.h"
#include "IconButtonPage.h"
#if __has_include("IconButtonPage.g.cpp")
#include "IconButtonPage.g.cpp"
#endif
using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	void IconButtonPage::NormalInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		NormalButton().Content(winrt::box_value(L"Clicked"));
	}

	void IconButtonPage::ToggleInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		ToggleButton().Content(winrt::box_value(L"Clicked"));
	}
}
