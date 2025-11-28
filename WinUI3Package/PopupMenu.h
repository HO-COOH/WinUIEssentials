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
#include "RadioPopupMenuItemGroup.h"

#pragma region Forward declaration
namespace winrt::WinUI3Package::implementation 
{
	struct PopupMenuFlyoutItem;
	struct TogglePopupMenuFlyoutItem;
	struct RadioPopupMenuFlyoutItem;
	struct PopupMenuFlyoutSubItem;
	struct PopupMenuFlyoutItemBase;
}
namespace Gdiplus
{
	class Brush;
}

#pragma endregion

/**
 * @brief Win32 style taskbar icon's context menu
 */
class PopupMenu : public MenuBase
{
	HMENU m_menu = CreatePopupMenu();

	std::optional<ThemeListener::Token> m_themeListenerToken;
	winrt::WinUI3Package::PopupMenuFlyout m_xamlMenu{ nullptr };
	std::optional<RadioPopupMenuItemGroup> m_radioGroup;

	void appendMenu(
		winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> xamlMenu,
		HMENU menu,
		int& index);

	static HBITMAP drawGlyph(
		UINT dpi, 
		winrt::Microsoft::UI::Xaml::ApplicationTheme theme, 
		winrt::Microsoft::UI::Xaml::Controls::SymbolIcon const& symbolIcon,
		bool isEnabled = true);

	static Gdiplus::Brush& getBrush(
		winrt::Microsoft::UI::Xaml::ApplicationTheme theme,
		bool isEnabled
	);

	static HBITMAP drawGlyph(
		UINT dpi, 
		winrt::Microsoft::UI::Xaml::ApplicationTheme theme, 
		winrt::Microsoft::UI::Xaml::Controls::FontIcon const& fontIcon,
		bool isEnabled = true);

	static void setMenuItemGlyph(
		winrt::Microsoft::UI::Xaml::Controls::IconElement const& icon, 
		HMENU menu, 
		UINT index, 
		UINT dpi, 
		winrt::Microsoft::UI::Xaml::ApplicationTheme theme,
		bool isEnabled);

	static void redrawMenuIcon(
		HMENU menu, 
		winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> const& item, 
		UINT dpi, 
		winrt::Microsoft::UI::Xaml::ApplicationTheme theme);
	
	//wraps up `GetMenuItemInfoW` because we use identifier instead of position here
	static BOOL getMenuItemInfo(HMENU hmenu, UINT item, LPMENUITEMINFOW info);

	//wraps up `SetMenuItemInfoW` because we use identifier instead of position here
	static BOOL setMenuItemInfo(HMENU hmenu, UINT item, LPMENUITEMINFOW info);

	//wraps up `DeleteMenu` because we use identifier instead of position here
	static BOOL deleteMenu(HMENU hemnu, UINT item);

	//wraps up `InsertMenuW` because we use identifier instead of position here
	static BOOL insertMenu(HMENU hmenu, UINT item, UINT flags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem);

	//to lookup `PopupMenuFlyoutItem` by menu id, used in `OnMenuClick()` 
	std::vector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> m_menuItemCache;

	//Inject `HMENU m_parentMenu` and `int index` into implementation type that derived from `PopupMenuFlyoutImplBase`
	void injectPopupMenuFlyoutItemImplBase(auto* implPtr, HMENU parentMenu, int index)
	{
		assert(implPtr);
		implPtr->m_parentMenu = parentMenu;
		implPtr->index = index;
		implPtr->m_parentMenuPtr = this;
	}
public:
	PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout);
	~PopupMenu();

	void Theme(winrt::Microsoft::UI::Xaml::ElementTheme value);


	void Show(POINT pt, HWND ownerHwnd);
	void OnMenuClick(int index);

	friend struct winrt::WinUI3Package::implementation::PopupMenuFlyoutItem;
	friend struct winrt::WinUI3Package::implementation::TogglePopupMenuFlyoutItem;
	friend struct winrt::WinUI3Package::implementation::RadioPopupMenuFlyoutItem;
	friend struct winrt::WinUI3Package::implementation::PopupMenuFlyoutSubItem;
	friend struct winrt::WinUI3Package::implementation::PopupMenuFlyoutItemBase;
};
