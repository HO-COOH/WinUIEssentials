#include "pch.h"
#include "ModernStandardWindowContextMenuPage.xaml.h"
#if __has_include("ModernStandardWindowContextMenuPage.g.cpp")
#include "ModernStandardWindowContextMenuPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void ModernStandardWindowContextMenuPage::StandardWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::StandardWindowWithMenu{}.Activate();
	}

	void ModernStandardWindowContextMenuPage::NonResizableWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const& sender, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		winrt::WinUI3Example::NonResizableWindowWithMenu{}.Activate();
	}


	void ModernStandardWindowContextMenuPage::EssentialWindowWithMenuButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::EssentialWindowWithMenu{}.Activate();
	}

}
