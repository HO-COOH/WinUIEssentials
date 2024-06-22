#include "pch.h"
#include "IconButtonPage.xaml.h"
#if __has_include("IconButtonPage.g.cpp")
#include "IconButtonPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void IconButtonPage::NormalInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		NormalButton().Content(winrt::box_value(L"Clicked"));
	}

	void IconButtonPage::ToggleInnerButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
	{
		ToggleButton().Content(winrt::box_value(L"Clicked"));
	}
}
