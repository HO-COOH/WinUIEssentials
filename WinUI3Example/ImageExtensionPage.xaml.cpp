#include "pch.h"
#include "ImageExtensionPage.xaml.h"
#if __has_include("ImageExtensionPage.g.cpp")
#include "ImageExtensionPage.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void ImageExtensionPage::SuccessLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Microsoft::UI::Xaml::Media::Imaging::SvgImageSource{ 
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_2012.svg"} 
		});
	}


	void ImageExtensionPage::FailedLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Microsoft::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_20.svg"}
		});
	}

}


