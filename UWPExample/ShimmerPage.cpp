#include "pch.h"
#include "ShimmerPage.h"
#if __has_include("ShimmerPage.g.cpp")
#include "ShimmerPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<ShimmerPage> s_tags{ L"shimmer", L"animation", L"control", L"composition" };

	void ShimmerPage::Image_ImageOpened(winrt::Windows::Foundation::IInspectable const&, winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		testShimmer().IsLoading(false);
	}
}
