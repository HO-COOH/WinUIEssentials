#pragma once
#include <Windows.h>
#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#endif
#include "MenuBase.h"
#include <vector>
class PopupMenu : public MenuBase
{
	HMENU m_menu = CreatePopupMenu();

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
public:
	PopupMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenuFlyout);
	std::vector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem::Click_revoker> m_menuItemCommandRevoker;
private:
	void appendMenu(
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> xamlMenu,
		HMENU menu);
#endif
public:
	~PopupMenu();

	void Show(POINT pt);
};
