#include "pch.h"
#include "WindowCaptionButtonThemeWorkaround.h"
#if __has_include("WindowCaptionButtonThemeWorkaround.g.cpp")
#include "WindowCaptionButtonThemeWorkaround.g.cpp"
#endif
#include <winrt/Windows.UI.ViewManagement.h>

namespace winrt::UWPPackage::implementation
{
	WindowCaptionButtonThemeWorkaround::WindowCaptionButtonThemeWorkaround()
	{
		ActualThemeChanged([titleBar = winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar()](winrt::Windows::UI::Xaml::FrameworkElement const& sender, winrt::Windows::Foundation::IInspectable const&)
		{
			switch (sender.ActualTheme())
			{
				case winrt::Windows::UI::Xaml::ElementTheme::Light:
					titleBar.ButtonForegroundColor(winrt::Windows::UI::Colors::Black());
					titleBar.ButtonHoverForegroundColor(winrt::Windows::UI::Colors::Black());
					break;
				case winrt::Windows::UI::Xaml::ElementTheme::Dark:
					titleBar.ButtonForegroundColor(winrt::Windows::UI::Colors::White());
					titleBar.ButtonHoverForegroundColor(winrt::Windows::UI::Colors::White());
					break;
				default:
					break;
			}
		});
	}
}
