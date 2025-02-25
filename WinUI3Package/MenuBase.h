#pragma once
#if __has_include("winrt/Microsoft.UI.Xaml.h")
#include <winrt/Microsoft.UI.Xaml.h>
#endif
#include "UxThemeWrapper.h"
class MenuBase
{
protected:
	winrt::Microsoft::UI::Xaml::ElementTheme m_theme{ winrt::Microsoft::UI::Xaml::ElementTheme::Default };
public:
#if __has_include("winrt/Microsoft.UI.Xaml.h")
	void Theme(winrt::Microsoft::UI::Xaml::ElementTheme value)
	{
		m_theme = value;
		switch (value)
		{
		case winrt::Microsoft::UI::Xaml::ElementTheme::Default:
			UxTheme{}.SetPreferredAppMode(PreferredAppMode::AllowDark);
			break;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
			UxTheme{}.SetPreferredAppMode(PreferredAppMode::ForceLight);
			break;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
			UxTheme{}.SetPreferredAppMode(PreferredAppMode::ForceDark);
			break;
		default:
			break;
		}
	}
	winrt::Microsoft::UI::Xaml::ElementTheme Theme()
	{
		return m_theme;
	}
#endif
};
