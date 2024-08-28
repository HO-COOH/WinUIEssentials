#include "pch.h"
#include "PopupMenu.h"
#include "TaskbarIconMessageWindow.h"
#include "IconUtils.h"
#include "AppsUseLightTheme.h"
#include "InvalidMenuItemIconTypeError.hpp"
#include "PopupMenuFlyoutItem.h"

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
void PopupMenu::appendMenu(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> xamlMenu, HMENU menu)
{
	int index{};
	AppsUseLightTheme theme;
	auto const dpi = Utils::GetPrimaryMonitorDpi();
	for (auto item : xamlMenu)
	{
		switch (item.Type())
		{
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutItem:
		{
			auto flyoutItem = item.as<winrt::WinUI3Package::PopupMenuFlyoutItem>();
			m_menuItemCache.push_back(flyoutItem);
			winrt::check_bool(AppendMenu(
				menu,
				NULL,
				m_menuItemCache.size() - 1,
				flyoutItem.Text().data()
			));

			if (auto icon = flyoutItem.Icon())
				setMenuItemGlyph(icon, menu, index, dpi, theme);
			break;
		}
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutSeparator:
		{
			winrt::check_bool(AppendMenu(
				menu,
				MF_SEPARATOR,
				NULL,
				NULL
			));
			break;
		}
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::SubMenu:
		{
			auto subItem = item.as<winrt::WinUI3Package::PopupMenuFlyoutSubItem>();
			auto subMenu = CreatePopupMenu();
			winrt::check_bool(AppendMenu(
				menu,
				MF_POPUP,
				reinterpret_cast<UINT_PTR>(subMenu),
				subItem.Text().data()));
			appendMenu(subItem.Items(), subMenu);
			break;
		}
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::ToggleItem:
		{
			auto toggleItem = item.as<winrt::WinUI3Package::TogglePopupMenuFlyoutItem>();
			winrt::check_bool(AppendMenu(
				menu,
				toggleItem.IsChecked() ? MF_CHECKED : MF_UNCHECKED,
				index,
				toggleItem.Text().data()
			));
			break;
		}
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::RadioItem:
		{
			auto radioItem = item.as<winrt::WinUI3Package::RadioPopupMenuFlyoutItem>();
			winrt::check_bool(AppendMenu(
				menu,
				NULL,
				index,
				radioItem.Text().data()
			));
			
			MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_FTYPE | MIIM_STATE };
			winrt::check_bool(GetMenuItemInfo(menu, index, true, &itemInfo));
			itemInfo.fType = MFT_RADIOCHECK;
			itemInfo.fState = radioItem.IsChecked() ? MFS_CHECKED : MFS_UNCHECKED;
			SetMenuItemInfo(menu, index, true, &itemInfo);
			auto err = GetLastError();
			break;
		}
		default:
			assert(false);
			break;
		}
		index++;
	}
}

HBITMAP PopupMenu::drawGlyph(HMENU menu, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, winrt::Microsoft::UI::Xaml::Controls::SymbolIcon const& symbolIcon)
{
	auto symbol = symbolIcon.Symbol();
	wchar_t s[2]{ static_cast<wchar_t>(symbol) };
	return Utils::DrawGlyph(s, theme, dpi);
}

HBITMAP PopupMenu::drawGlyph(HMENU menu, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, winrt::Microsoft::UI::Xaml::Controls::FontIcon const& fontIcon)
{
	auto fontFamily = fontIcon.FontFamily().Source();
	auto glyph = fontIcon.Glyph();
	return Utils::DrawGlyph(glyph, theme, dpi);
}

void PopupMenu::setMenuItemGlyph(winrt::Microsoft::UI::Xaml::Controls::IconElement const& icon, HMENU menu, UINT index, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme)
{
	if (auto symbolIcon = icon.try_as<winrt::Microsoft::UI::Xaml::Controls::SymbolIcon>())
	{
		MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_FTYPE | MIIM_BITMAP };
		winrt::check_bool(GetMenuItemInfo(menu, index, true, &itemInfo));
		itemInfo.hbmpItem = drawGlyph(menu, dpi, theme, symbolIcon);
		winrt::check_bool(SetMenuItemInfo(menu, index, true, &itemInfo));
	}
	else if (auto fontIcon = icon.try_as<winrt::Microsoft::UI::Xaml::Controls::FontIcon>())
	{
		MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_FTYPE | MIIM_BITMAP };
		winrt::check_bool(GetMenuItemInfo(menu, index, true, &itemInfo));
		itemInfo.hbmpItem = drawGlyph(menu, dpi, theme, fontIcon);
		winrt::check_bool(SetMenuItemInfo(menu, index, true, &itemInfo));
	}
	else
	{
		throw InvalidMenuItemIconTypeError{};
	}
}

void PopupMenu::redrawMenuIcon(HMENU menu, winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> const& items, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme)
{
	int menuItemCount = GetMenuItemCount(menu);
	winrt::check_bool(menuItemCount != -1);
	MENUITEMINFO info{ .cbSize = sizeof(info), .fMask = MIIM_BITMAP | MIIM_SUBMENU };
	for (int i = 0; i < menuItemCount; ++i)
	{
		winrt::check_bool(GetMenuItemInfo(menu, i, true, &info));
		if (info.hbmpItem || info.hSubMenu)
		{
			auto itemToRedraw = items.GetAt(i);
			switch (itemToRedraw.Type())
			{
			case winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutItem:
				if (auto icon = itemToRedraw.as<winrt::WinUI3Package::PopupMenuFlyoutItem>().Icon())
					setMenuItemGlyph(icon, menu, i, dpi, theme);
				break;
			case winrt::WinUI3Package::PopupMenuFlyoutItemType::SubMenu:
			{
				assert(info.hSubMenu);
				redrawMenuIcon(
					info.hSubMenu,
					itemToRedraw.as<winrt::WinUI3Package::PopupMenuFlyoutSubItem>().Items(),
					dpi,
					theme
				);
				break;
			}
			default:
				break;
			}
		}
	}
}

PopupMenu::PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout)
{
	if (m_xamlMenu = xamlMenuFlyout.try_as<winrt::WinUI3Package::PopupMenuFlyout>())
		appendMenu(m_xamlMenu.Items(), m_menu);
}
#endif

PopupMenu::~PopupMenu()
{
	winrt::check_bool(DestroyMenu(m_menu));
}

void PopupMenu::Theme(winrt::Microsoft::UI::Xaml::ElementTheme value)
{
	MenuBase::Theme(value);
	if (value == winrt::Microsoft::UI::Xaml::ElementTheme::Default)
	{
		m_themeListenerToken = ThemeListener::Add([this](winrt::Microsoft::UI::Xaml::ApplicationTheme value) {
			auto const dpi = Utils::GetPrimaryMonitorDpi();
			redrawMenuIcon(m_menu, m_xamlMenu.Items(),  dpi, value);
		});
	}
	else
		m_themeListenerToken.reset();
}

void PopupMenu::Show(POINT pt, HWND ownerHwnd)
{
	winrt::check_bool(TrackPopupMenuEx(
		m_menu,
		TPM_LEFTALIGN,
		pt.x,
		pt.y,
		ownerHwnd,
		nullptr
	));
}

void PopupMenu::OnMenuClick(int index)
{
	winrt::get_self<winrt::WinUI3Package::implementation::PopupMenuFlyoutItem>(m_menuItemCache[index])->m_clickEvent(m_menuItemCache[index], nullptr);
}
