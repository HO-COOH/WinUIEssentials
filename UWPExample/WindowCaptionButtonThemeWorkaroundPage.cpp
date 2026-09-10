#include "pch.h"
#include "WindowCaptionButtonThemeWorkaroundPage.h"
#if __has_include("WindowCaptionButtonThemeWorkaroundPage.g.cpp")
#include "WindowCaptionButtonThemeWorkaroundPage.g.cpp"
#endif
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include "PageTagRegister.h"
#include "CreateWindowHelper.hpp"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<WindowCaptionButtonThemeWorkaroundPage> s_tags{ L"captionbutton", L"window", L"workaround", L"theme"};


	void WindowCaptionButtonThemeWorkaroundPage::CreateWorkaroundWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		CreateWindowWithPage<winrt::UWPExample::WindowCaptionButtonWithWorkaround>();
	}

	void WindowCaptionButtonThemeWorkaroundPage::CompareWindowsButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		CreateWindowWithPage<winrt::UWPExample::DefaultWindowBrokenCaptionButton>();
		CreateWindowWithPage<winrt::UWPExample::WindowCaptionButtonWithWorkaround>();
	}

	void WindowCaptionButtonThemeWorkaroundPage::CreateDefaultWindowButton_Click(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Windows::UI::Xaml::RoutedEventArgs const&)
	{
		CreateWindowWithPage<winrt::UWPExample::DefaultWindowBrokenCaptionButton>();
	}

}
