#pragma once

#include "MenuBase.h"
#include "TransparentMenuFlyoutHost.h"

class MenuFlyoutWrapper : public MenuBase
{
	winrt::Microsoft::UI::Xaml::Controls::MenuFlyout m_menu;
	TransparentMenuFlyoutHost m_menuHost;

	void showImpl();
public:
	MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& flyout);

	void Show(POINT p);
};
