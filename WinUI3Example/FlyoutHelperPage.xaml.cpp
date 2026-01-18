#include "pch.h"
#include "FlyoutHelperPage.xaml.h"
#if __has_include("FlyoutHelperPage.g.cpp")
#include "FlyoutHelperPage.g.cpp"
#endif


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	std::vector<winrt::Windows::Foundation::IInspectable> FlyoutHelperPage::Components()
	{
		return std::vector
		{
			winrt::box_value(winrt::WinUI3Example::ComponentInfo{.Name = L"FlyoutHelper", .Xaml = false, .Idl = true, .H = true, .Cpp = true}),
		};
	}
}
