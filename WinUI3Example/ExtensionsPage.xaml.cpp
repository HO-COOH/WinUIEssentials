#include "pch.h"
#include "ExtensionsPage.xaml.h"
#if __has_include("ExtensionsPage.g.cpp")
#include "ExtensionsPage.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void ExtensionsPage::SuccessLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Microsoft::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_2012.svg"}
		});
	}


	void ExtensionsPage::FailedLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Microsoft::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_20.svg"}
		});
	}
}
