#include "pch.h"
#include "ShimmerPage.h"
#if __has_include("ShimmerPage.g.cpp")
#include "ShimmerPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::UWPExample::implementation
{
	void ShimmerPage::Image_ImageOpened(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		testShimmer().IsLoading(false);
	}
}
