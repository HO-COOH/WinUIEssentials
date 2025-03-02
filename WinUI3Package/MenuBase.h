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
		static UxTheme s_uxTheme;
		switch (value)
		{
		case winrt::Microsoft::UI::Xaml::ElementTheme::Default:
			s_uxTheme.SetPreferredAppMode(PreferredAppMode::AllowDark);
			break;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Light:
			s_uxTheme.SetPreferredAppMode(PreferredAppMode::ForceLight);
			break;
		case winrt::Microsoft::UI::Xaml::ElementTheme::Dark:
			s_uxTheme.SetPreferredAppMode(PreferredAppMode::ForceDark);
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
