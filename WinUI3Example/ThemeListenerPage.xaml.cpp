#include "pch.h"
#include "ThemeListenerPage.xaml.h"
#if __has_include("ThemeListenerPage.g.cpp")
#include "ThemeListenerPage.g.cpp"
#endif

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
{
	winrt::hstring ThemeListenerPage::ElementThemeToString(winrt::Microsoft::UI::Xaml::ElementTheme theme)
	{
		switch (theme)
		{
			case winrt::Microsoft::UI::Xaml::ElementTheme::Dark: return L"Dark";
			case winrt::Microsoft::UI::Xaml::ElementTheme::Light: return L"Light";
			default: return L"Default";
		}
	}

}

