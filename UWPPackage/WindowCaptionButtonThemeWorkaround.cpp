#include "pch.h"
#include "WindowCaptionButtonThemeWorkaround.h"
#if __has_include("WindowCaptionButtonThemeWorkaround.g.cpp")
#include "WindowCaptionButtonThemeWorkaround.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
	WindowCaptionButtonThemeWorkaround::WindowCaptionButtonThemeWorkaround()
		: m_titleBar{ winrt::Windows::UI::ViewManagement::ApplicationView::GetForCurrentView().TitleBar() }
	{
		Loading([this](auto&&...)
		{
			setCaptionButtonTheme(ActualTheme());
		});

		ActualThemeChanged([this](auto&&...)
		{
			setCaptionButtonTheme(ActualTheme());
		});
	}

	void WindowCaptionButtonThemeWorkaround::setCaptionButtonTheme(winrt::Windows::UI::Xaml::ElementTheme const& theme)
	{
		auto const foreground = theme == winrt::Windows::UI::Xaml::ElementTheme::Dark ?
			winrt::Windows::UI::Colors::White() : winrt::Windows::UI::Colors::Black();

		m_titleBar.ButtonForegroundColor(foreground);
		m_titleBar.ButtonHoverForegroundColor(foreground);
	}
}
