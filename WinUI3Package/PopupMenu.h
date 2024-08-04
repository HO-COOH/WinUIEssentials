#pragma once
#include <Windows.h>
#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#endif
class PopupMenu
{
	HMENU m_menu = CreatePopupMenu();
public:
#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
	PopupMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenuFlyout);
#endif
	~PopupMenu();
};
