#pragma once
#include "ThemeListener.h"
#include "TaskbarIconBase.h"
#include <winrt/Microsoft.UI.Xaml.h>

/**
 * @brief This class adds additional funcionalities that:
 *  Listen to system theme setting event and change the icon accordingly
 * Icon is set by using the setter function `IconLight(hicon)` for icon to show under light mode and 
 * `IconDark(hicon)` for icon to show under dark mode
 */
class ThemeAdaptiveIcon : public TaskbarIconBase
{
	HICON m_iconLight{};
	HICON m_iconDark{};
	ThemeListener::Token m_themeListenerToken;

	void onThemeChanged();
	
	void addOnThemeChangedIfSet();
public:
	ThemeAdaptiveIcon() = default;
	ThemeAdaptiveIcon(HICON iconLight, HICON iconDark);
	
	ThemeAdaptiveIcon& IconLight(HICON value);
	ThemeAdaptiveIcon& IconDark(HICON value);

	void Show();
};