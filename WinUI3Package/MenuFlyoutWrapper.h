#pragma once

#include "MenuBase.h"
#include "TransparentMenuFlyoutHost.h"
#include "MenuFlyoutItemPaddingWorkaroundWrapper.hpp"
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

/**
 * @brief This class wraps up a `Microsoft.UI.Xaml.Controls.MenuFlyout` with a `TransparentMenuFlyoutHost` to show the menu
 *  The menu will be show at the specified point, with the call to `Show(point)`
 */
class MenuFlyoutWrapper : public MenuBase, private MenuFlyoutItemPaddingWorkaroundWrapper
{
	winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase m_menu;
	TransparentMenuFlyoutHost m_menuHost;
public:
	MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& flyout);

	void Show(POINT p);
};
