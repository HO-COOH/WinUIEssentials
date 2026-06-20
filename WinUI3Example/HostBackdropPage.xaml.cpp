#include "pch.h"
#include "HostBackdropPage.xaml.h"
#if __has_include("HostBackdropPage.g.cpp")
#include "HostBackdropPage.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	void HostBackdropPage::Button_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::HostBackdropWindow{}.Activate();
	}
}
