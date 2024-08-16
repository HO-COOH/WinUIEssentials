#pragma once

#include "MenuBase.h"
#include "TransparentMenuFlyoutHost.h"
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>

class MenuFlyoutWrapper : public MenuBase
{
	winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase m_menu;
	TransparentMenuFlyoutHost m_menuHost;

	void showImpl();
public:
	MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& flyout);

	void Show(POINT p);
};
