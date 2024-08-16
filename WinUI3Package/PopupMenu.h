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

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
public:
	PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout);
	std::vector<std::pair<winrt::Microsoft::UI::Xaml::Input::ICommand, winrt::Windows::Foundation::IInspectable>> m_commands;
private:
	void appendMenu(
		winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> xamlMenu,
		HMENU menu);
#endif
public:
	~PopupMenu();

	void Show(POINT pt, HWND ownerHwnd);
	void OnMenuClick(int index);
};
