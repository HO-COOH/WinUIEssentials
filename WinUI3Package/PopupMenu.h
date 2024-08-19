#pragma once
#include <Windows.h>
#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#endif

#include "MenuBase.h"
#include <vector>
#include <utility>

/**
 * @brief Win32 style taskbar icon's context menu
 */
class PopupMenu : public MenuBase
{
	HMENU m_menu = CreatePopupMenu();

private:
	void appendMenu(
		winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> xamlMenu,
		HMENU menu);
public:
	PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout);
	~PopupMenu();

	void Show(POINT pt, HWND ownerHwnd);
	void OnMenuClick(int index);
};
