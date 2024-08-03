#pragma once
#include "ThemeListener.h"
#include "TaskbarIconBase.h"
#include <winrt/Microsoft.UI.Xaml.h>

class ThemeAdaptiveIcon : public TaskbarIconBase
{
	HICON m_iconLight{};
	HICON m_iconDark{};
	ThemeListener::Token m_themeListenerToken;

	void onThemeChanged(winrt::Microsoft::UI::Xaml::ApplicationTheme theme);
	
	void addOnThemeChangedIfSet();
public:
	ThemeAdaptiveIcon() = default;
	ThemeAdaptiveIcon(HICON iconLight, HICON iconDark);
	
	ThemeAdaptiveIcon& IconLight(HICON value);
	ThemeAdaptiveIcon& IconDark(HICON value);

	void Show();
};