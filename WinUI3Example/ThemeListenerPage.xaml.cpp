#include "pch.h"
#include "ThemeListenerPage.xaml.h"
#if __has_include("ThemeListenerPage.g.cpp")
#include "ThemeListenerPage.g.cpp"
#endif
#include <AppsUseLightTheme.h>

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	void ThemeListenerPage::TextBlock_Loaded(
		winrt::Windows::Foundation::IInspectable const&, 
		winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
	{
		updateThemeState(AppsUseLightTheme{});
		updateThemeState(ActualTheme());
		m_themeChangedHandlerToken = ThemeListener::Add([this](auto theme) {updateThemeState(theme); });
	}


	void ThemeListenerPage::Page_ActualThemeChanged(
		winrt::Microsoft::UI::Xaml::FrameworkElement const& , 
		winrt::Windows::Foundation::IInspectable const&)
	{
		updateThemeState(ActualTheme());
	}


	void ThemeListenerPage::updateThemeState(winrt::Microsoft::UI::Xaml::ApplicationTheme theme)
	{
		SystemTheme().Text(theme == winrt::Microsoft::UI::Xaml::ApplicationTheme::Light ? L"Light" : L"Dark");
	}

	void ThemeListenerPage::updateThemeState(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		std::wstring_view text;
		switch (theme)
		{
		case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
			text = L"Dark";
			break;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
			text = L"Light";
			break;
		default:
			text = L"Default";
			break;
		}

		CurrentTheme().Text(text);
	}

}

