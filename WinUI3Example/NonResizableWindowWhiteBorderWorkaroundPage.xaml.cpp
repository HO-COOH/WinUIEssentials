#include "pch.h"
#include "NonResizableWindowWhiteBorderWorkaroundPage.xaml.h"
#if __has_include("NonResizableWindowWhiteBorderWorkaroundPage.g.cpp")
#include "NonResizableWindowWhiteBorderWorkaroundPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<NonResizableWindowWhiteBorderWorkaroundPage> s_tags{ L"nonresizablewindowwhiteborderworkaround", L"nonresizable", L"whiteborder", L"border", L"window", L"workaround" };

	void NonResizableWindowWhiteBorderWorkaroundPage::CreateNonResizableBtn_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::NormalNonResizableNoBorderWindow{}.Activate();
	}

	void NonResizableWindowWhiteBorderWorkaroundPage::CreateNonResizableWithWorkaroundBtn_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::NonResizableNoBorderWindowWithWorkaround{}.Activate();
	}
}
