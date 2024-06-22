#include "pch.h"
#include "TitleBarPage.xaml.h"
#if __has_include("TitleBarPage.g.cpp")
#include "TitleBarPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{

	void TitleBarPage::CreateWin32Window_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::Win32TitleBar{}.Activate();
	}


	void TitleBarPage::CreateCustomWindow_Click(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		WinUI3Example::CustomTitleBar{}.Activate();
	}

}

