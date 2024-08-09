#pragma once
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "MenuBase.h"
class MenuFlyoutWrapper : public MenuBase
{
	winrt::Microsoft::UI::Xaml::Controls::MenuFlyout m_menu;
public:
	MenuFlyoutWrapper(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& flyout);

};
