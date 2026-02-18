#include "pch.h"
#include "TeachingTipHelperPage.xaml.h"
#if __has_include("TeachingTipHelperPage.g.cpp")
#include "TeachingTipHelperPage.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	void TeachingTipHelperPage::TestButton1_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton1TeachingTip().IsOpen(true);
	}
}
