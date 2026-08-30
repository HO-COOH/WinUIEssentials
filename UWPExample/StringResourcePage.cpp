#include "pch.h"
#include "StringResourcePage.h"
#if __has_include("StringResourcePage.g.cpp")
#include "StringResourcePage.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
	void StringResourcePage::CreateContentDialogButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::UWPExample::LocalizedContentDialog dialog;
		dialog.ShowAsync();
	}
}
