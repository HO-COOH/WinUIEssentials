#pragma once
#if __has_include("winrt/Microsoft.UI.Xaml.h")
#include <winrt/Microsoft.UI.Xaml.h>
#endif
class MenuBase
{
	winrt::Microsoft::UI::Xaml::ElementTheme m_theme{ winrt::Microsoft::UI::Xaml::ElementTheme::Default };
public:
#if __has_include("winrt/Microsoft.UI.Xaml.h")
	void Theme(winrt::Microsoft::UI::Xaml::ElementTheme value)
	{
		m_theme = value;
	}
	winrt::Microsoft::UI::Xaml::ElementTheme Theme()
	{
		return m_theme;
	}
#endif
};
