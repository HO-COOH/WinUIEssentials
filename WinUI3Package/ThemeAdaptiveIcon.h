#pragma once
#include "ThemeListener.h"
#include <winrt/Microsoft.UI.Xaml.h>
#include "NotifyIconData.h"
class ThemeAdaptiveIcon
{
	HICON m_iconLight;
	HICON m_iconDark;
	ThemeListener::Token m_themeListenerToken;
	NotifyIconData m_iconData;
	void onThemeChanged(winrt::Microsoft::UI::Xaml::ApplicationTheme theme);
public:
	ThemeAdaptiveIcon(HICON iconLight, HICON iconDark);

	~ThemeAdaptiveIcon();
};