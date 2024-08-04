#include "pch.h"
#include "PopupMenu.h"

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
PopupMenu::PopupMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenuFlyout)
{
	for (auto const& item : xamlMenuFlyout.Items())
	{
		if (auto menuItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>())
		{
			winrt::check_bool(AppendMenu(
				m_menu,
				)
		}
		else if (auto separator = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSeparator>())
		{

		}
		else if (auto subItem = item.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSubItem>())
		{

		}
	}
}
#endif

PopupMenu::~PopupMenu()
{
	winrt::check_bool(DestroyMenu(m_menu));
}
