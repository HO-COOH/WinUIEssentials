#pragma once

#include "MenuBase.h"
#include "TransparentMenuFlyoutHost.h"
#include "MenuFlyoutItemPaddingWorkaroundWrapper.hpp"
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include "ThemeListener.h"
#include <optional>

/**
 * @brief This class wraps up a `FlyoutBase` (MenuFlyout or Flyout) with a `TransparentMenuFlyoutHost` to show the menu
 *  The menu will be show at the specified point, with the call to `Show(point)`
 *  For `MenuFlyout`, the padding workaround is applied on first show.
 */
class MenuFlyoutWrapper : public MenuBase, private MenuFlyoutItemPaddingWorkaroundWrapper
{
	winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase m_menu;
	TransparentMenuFlyoutHost m_menuHost;
	std::optional<ThemeListener::Token> m_themeListenerToken;

	void applySystemTheme();
public:
	MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& flyout);

	void Theme(winrt::Microsoft::UI::Xaml::ElementTheme value);
	void Show(POINT p);
};
