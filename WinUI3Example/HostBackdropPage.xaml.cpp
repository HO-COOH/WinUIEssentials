#include "pch.h"
#include "HostBackdropPage.xaml.h"
#if __has_include("HostBackdropPage.g.cpp")
#include "HostBackdropPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<HostBackdropPage> s_tags{ L"hostbackdropwindow", L"hostbackdrop", L"backdrop", L"acrylic", L"blur", L"window" };

	void HostBackdropPage::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::HostBackdropWindow{}.Activate();
	}
}
