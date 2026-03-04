#include "pch.h"
#include "CaptionButtonThemeWorkaroundPage.xaml.h"
#if __has_include("CaptionButtonThemeWorkaroundPage.g.cpp")
#include "CaptionButtonThemeWorkaroundPage.g.cpp"
#endif
#include "HwndHelper.hpp"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void CaptionButtonThemeWorkaroundPage::CreateDefaultWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::DefaultWindowBrokenCaptionButton{}.Activate();
	}

	void CaptionButtonThemeWorkaroundPage::CreateWorkaroundWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::DefaultWindowCaptionButtonWorkaround{}.Activate();
	}

	void CaptionButtonThemeWorkaroundPage::CompareWindowsButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		winrt::WinUI3Example::DefaultWindowBrokenCaptionButton brokenWindow;
		winrt::WinUI3Example::DefaultWindowCaptionButtonWorkaround fixedWindow;

		auto monitor = MonitorFromWindow(GetHwnd(brokenWindow), MONITOR_DEFAULTTONEAREST);
		MONITORINFO info
		{
			.cbSize = sizeof(info)
		};
		GetMonitorInfo(monitor, &info);
		auto const halfWidth = (info.rcWork.right - info.rcWork.left) / 2;
		auto const height = info.rcWork.bottom - info.rcWork.top;
		brokenWindow.AppWindow().MoveAndResize(winrt::Windows::Graphics::RectInt32{
			.X = info.rcWork.left,
			.Y = info.rcWork.top,
			.Width = halfWidth,
			.Height = height
		});
		fixedWindow.AppWindow().MoveAndResize(winrt::Windows::Graphics::RectInt32{
			.X = info.rcWork.left + halfWidth,
			.Y = info.rcWork.top,
			.Width = halfWidth,
			.Height = height
		});
		brokenWindow.Activate();
		fixedWindow.Activate();
	}
	std::vector<winrt::Windows::Foundation::IInspectable> CaptionButtonThemeWorkaroundPage::Components()
	{
		return std::vector
		{
			winrt::box_value(winrt::WinUI3Example::ComponentInfo{.Name = L"CaptionButtonThemeWorkaround", .Xaml = false, .Idl = true, .H = true, .Cpp = true}),
		};
	}
}


