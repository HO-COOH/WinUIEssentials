#include "pch.h"
#include "CaptionButtonThemeWorkaroundPage.xaml.h"
#if __has_include("CaptionButtonThemeWorkaroundPage.g.cpp")
#include "CaptionButtonThemeWorkaroundPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void CaptionButtonThemeWorkaroundPage::CreateDefaultWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::DefaultWindowBrokenCaptionButton{}.Activate();
	}

	void CaptionButtonThemeWorkaroundPage::CreateWorkaroundWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::DefaultWindowCaptionButtonWorkaround{}.Activate();
	}

	void CaptionButtonThemeWorkaroundPage::CompareWindowsButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::DefaultWindowBrokenCaptionButton{}.Activate();
		winrt::WinUI3Example::DefaultWindowCaptionButtonWorkaround{}.Activate();
	}
}


