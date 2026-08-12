#include "pch.h"
#include "NonMaximizableWindowWorkaroundPage.xaml.h"
#if __has_include("NonMaximizableWindowWorkaroundPage.g.cpp")
#include "NonMaximizableWindowWorkaroundPage.g.cpp"
#endif
#include "PageTagRegister.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<NonMaximizableWindowWorkaroundPage> s_tags{ L"nonmaximizablewindowworkaround", L"nonmaximizable", L"maximize", L"window", L"workaround" };

	void NonMaximizableWindowWorkaroundPage::NormalButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::NormalNonMaximizableWindow{}.Activate();
	}

	void NonMaximizableWindowWorkaroundPage::WorkaroundButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::NonMaximizableWindowWithWorkaround{}.Activate();
	}
}
