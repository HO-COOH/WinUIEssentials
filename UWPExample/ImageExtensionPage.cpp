#include "pch.h"
#include "ImageExtensionPage.h"
#if __has_include("ImageExtensionPage.g.cpp")
#include "ImageExtensionPage.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	void ImageExtensionPage::SuccessLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_2012.svg"}
			});
	}


	void ImageExtensionPage::FailedLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_20.svg"}
			});
	}
}
