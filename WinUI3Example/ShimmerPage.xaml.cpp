#include "pch.h"
#include "ShimmerPage.xaml.h"
#if __has_include("ShimmerPage.g.cpp")
#include "ShimmerPage.g.cpp"
#endif
#include "PageTagRegister.h"

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	static PageTagRegister<ShimmerPage> s_tags{ L"shimmer", L"animation", L"control", L"composition" };

	void ShimmerPage::Image_ImageOpened(winrt::Windows::Foundation::IInspectable const&, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		testShimmer().IsLoading(false);
	}
}
