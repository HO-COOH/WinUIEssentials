#include "pch.h"
#include "TeachingTipHelperPage.xaml.h"
#if __has_include("TeachingTipHelperPage.g.cpp")
#include "TeachingTipHelperPage.g.cpp"
#endif
#include "PageTagRegister.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<TeachingTipHelperPage> s_tags{ L"teachingtip", L"acrylic", L"control", L"workaround" };

	void TeachingTipHelperPage::TestButton1_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton1TeachingTip().IsOpen(true);
	}

	void TeachingTipHelperPage::TestButton2_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton2TeachingTip().IsOpen(true);
	}

	void TeachingTipHelperPage::TestButton3_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton3TeachingTip().IsOpen(true);
	}

	void TeachingTipHelperPage::TestButton4_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton4TeachingTip().IsOpen(true);
	}

	void TeachingTipHelperPage::TestButton5_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton5TeachingTip().IsOpen(true);
	}

	void TeachingTipHelperPage::TestButton6_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		TestButton6TeachingTip().IsOpen(true);
	}
}
