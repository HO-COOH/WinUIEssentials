#pragma once
#include <Windows.h>
#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#endif

#include "MenuBase.h"
#include <vector>
#include <utility>
#include <optional>
#include "ThemeListener.h"
/**
 * @brief Win32 style taskbar icon's context menu
 */
class PopupMenu : public MenuBase
{
	HMENU m_menu = CreatePopupMenu();

	std::optional<ThemeListener::Token> m_themeListenerToken;
	winrt::WinUI3Package::PopupMenuFlyout m_xamlMenu{ nullptr };
private:
	void appendMenu(
		winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> xamlMenu,
		HMENU menu);

	static HBITMAP drawGlyph(HMENU menu, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, winrt::Microsoft::UI::Xaml::Controls::SymbolIcon const& symbolIcon);
	static HBITMAP drawGlyph(HMENU menu, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, winrt::Microsoft::UI::Xaml::Controls::FontIcon const& fontIcon);
	static void setMenuItemGlyph(winrt::Microsoft::UI::Xaml::Controls::IconElement const& icon, HMENU menu, UINT index, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme);
	static void redrawMenuIcon(HMENU menu, winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> const& item, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme);

	std::vector<winrt::WinUI3Package::PopupMenuFlyoutItem> m_menuItemCache;
public:
	PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout);
	~PopupMenu();

	void Theme(winrt::Microsoft::UI::Xaml::ElementTheme value);

	void Show(POINT pt, HWND ownerHwnd);
	void OnMenuClick(int index);
};
