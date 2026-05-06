#include "pch.h"
#include "ExtensionsPage.h"
#if __has_include("ExtensionsPage.g.cpp")
#include "ExtensionsPage.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>

namespace winrt::UWPExample::implementation
{
	void ExtensionsPage::SuccessLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_2012.svg"}
		});
	}


	void ExtensionsPage::FailedLoadButton_Click(
		winrt::Windows::Foundation::IInspectable const&,
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		Image().Source(winrt::Windows::UI::Xaml::Media::Imaging::SvgImageSource{
			winrt::Windows::Foundation::Uri{L"https://upload.wikimedia.org/wikipedia/commons/5/5f/Windows_logo_-_20.svg"}
		});
	}
}
