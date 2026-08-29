#include "pch.h"
#include "StringResourcePage.xaml.h"
#if __has_include("StringResourcePage.g.cpp")
#include "StringResourcePage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void StringResourcePage::CreateDialogButton_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::WinUI3Example::LocalizedContentDialog dialog;
		dialog.XamlRoot(XamlRoot());
		dialog.ShowAsync();
	}

	void StringResourcePage::CreateWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::WinUI3Example::LocalizedWindow{}.Activate();
	}
}
