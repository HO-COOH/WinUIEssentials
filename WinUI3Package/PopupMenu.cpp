#include "pch.h"
#include "PopupMenu.h"
#include "TaskbarIconMessageWindow.h"
#include "IconUtils.h"
#include "ThemeSettingsImpl.hpp"
#include "InvalidMenuItemIconTypeError.hpp"
#include <gdiplus.h>

#pragma region PopupMenuItem Implementation headers
#include "PopupMenuFlyoutItem.h"
#include "PopupMenuFlyoutSubItem.h"
#include "TogglePopupMenuFlyoutItem.h"
#include "RadioPopupMenuFlyoutItem.h"
#pragma endregion

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
void PopupMenu::appendMenu(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> xamlMenu, HMENU menu, int& index)
{
	auto const dpi = Utils::GetPrimaryMonitorDpi();
	for (auto item : xamlMenu)
	{
		assert(index == m_menuItemCache.size());
		m_menuItemCache.push_back(item);
		if (item.Visibility() == winrt::Microsoft::UI::Xaml::Visibility::Collapsed)
		{
			++index;
			continue;
		}

		switch (item.Type())
		{
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutItem:
		{
			auto flyoutItem = item.as<winrt::WinUI3Package::PopupMenuFlyoutItem>();
			injectPopupMenuFlyoutItemImplBase(
				winrt::get_self<winrt::WinUI3Package::implementation::PopupMenuFlyoutItem>(flyoutItem),
				menu,
				index);

			auto const isEnabled = item.IsEnabled();
			winrt::check_bool(AppendMenu(
				menu,
				isEnabled? NULL : MF_GRAYED,
				index,
				flyoutItem.Text().data()
			));

			if (auto icon = flyoutItem.Icon())
			{
				setMenuItemGlyph(
					icon, 
					menu, 
					index, 
					dpi, 
					ThemeSettingsImpl::AppsUseLightTheme()? winrt::Microsoft::UI::Xaml::ApplicationTheme::Light : winrt::Microsoft::UI::Xaml::ApplicationTheme::Dark,
					true
				);
			}
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
			injectPopupMenuFlyoutItemImplBase(
				winrt::get_self<winrt::WinUI3Package::implementation::PopupMenuFlyoutSubItem>(subItem),
				menu,
				index);
			
			winrt::check_bool(AppendMenu(
				menu,
				MF_POPUP,
				reinterpret_cast<UINT_PTR>(subMenu),
				subItem.Text().data()));
			appendMenu(subItem.Items(), subMenu, ++index);
			break;
		}
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::ToggleItem:
		{
			auto toggleItem = item.as<winrt::WinUI3Package::TogglePopupMenuFlyoutItem>();
			injectPopupMenuFlyoutItemImplBase(
				winrt::get_self<winrt::WinUI3Package::implementation::TogglePopupMenuFlyoutItem>(toggleItem),
				menu,
				index);

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
			auto radioItemImpl = winrt::get_self<winrt::WinUI3Package::implementation::RadioPopupMenuFlyoutItem>(radioItem);

			injectPopupMenuFlyoutItemImplBase(
				winrt::get_self<winrt::WinUI3Package::implementation::RadioPopupMenuFlyoutItem>(radioItem),
				menu,
				index);

			winrt::check_bool(AppendMenu(
				menu,
				NULL,
				index,
				radioItemImpl->Text().data()
			));
			

			auto const isChecked = radioItemImpl->IsChecked();
			MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_FTYPE | MIIM_STATE };
			itemInfo.fType = MFT_RADIOCHECK;
			itemInfo.fState = isChecked ? MFS_CHECKED : MFS_UNCHECKED;
			setMenuItemInfo(menu, index, &itemInfo);

			if (!m_radioGroup)
				m_radioGroup.emplace();
			radioItemImpl->SetGroupHelper(*m_radioGroup);
			if (auto group = radioItemImpl->GroupName(); !group.empty())
			{
				if (isChecked)
					m_radioGroup->SetCheckedItem(radioItem);
			}
			break;
		}
		default:
			assert(false);
			break;
		}
		++index;
	}
}

HBITMAP PopupMenu::drawGlyph(UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, winrt::Microsoft::UI::Xaml::Controls::SymbolIcon const& symbolIcon, bool isEnabled)
{
	auto symbol = symbolIcon.Symbol();
	wchar_t s[2]{ static_cast<wchar_t>(symbol) };
	return Utils::DrawGlyph(s, getBrush(theme, isEnabled), dpi);
}

Gdiplus::Brush& PopupMenu::getBrush(winrt::Microsoft::UI::Xaml::ApplicationTheme theme, bool isEnabled)
{
	if (!isEnabled)
	{
		static Gdiplus::SolidBrush s_disabledBrush{ Gdiplus::Color::Gray };
		return s_disabledBrush;
	}

	if (theme == winrt::Microsoft::UI::Xaml::ApplicationTheme::Light)
	{
		static Gdiplus::SolidBrush s_lightBrush{ Gdiplus::Color::Black };
		return s_lightBrush;
	}
	else
	{
		static Gdiplus::SolidBrush s_darkBrush{ Gdiplus::Color::White };
		return s_darkBrush;
	}
}

HBITMAP PopupMenu::drawGlyph(UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, winrt::Microsoft::UI::Xaml::Controls::FontIcon const& fontIcon, bool isEnabled)
{
	auto fontFamily = fontIcon.FontFamily().Source();
	auto glyph = fontIcon.Glyph();
	return Utils::DrawGlyph(glyph, getBrush(theme, isEnabled), dpi);
}

void PopupMenu::setMenuItemGlyph(winrt::Microsoft::UI::Xaml::Controls::IconElement const& icon, HMENU menu, UINT index, UINT dpi, winrt::Microsoft::UI::Xaml::ApplicationTheme theme, bool isEnabled)
{
	if (auto symbolIcon = icon.try_as<winrt::Microsoft::UI::Xaml::Controls::SymbolIcon>())
	{
		MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_BITMAP };
		itemInfo.hbmpItem = drawGlyph(dpi, theme, symbolIcon, isEnabled);
		winrt::check_bool(setMenuItemInfo(menu, index, &itemInfo));
	}
	else if (auto fontIcon = icon.try_as<winrt::Microsoft::UI::Xaml::Controls::FontIcon>())
	{
		MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_BITMAP };
		itemInfo.hbmpItem = drawGlyph(dpi, theme, fontIcon, isEnabled);
		winrt::check_bool(setMenuItemInfo(menu, index, &itemInfo));
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
					setMenuItemGlyph(icon, menu, i, dpi, theme, itemToRedraw.IsEnabled());
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

BOOL PopupMenu::getMenuItemInfo(HMENU hmenu, UINT item, LPMENUITEMINFOW info)
{
	return GetMenuItemInfo(hmenu, item, false, info);
}

BOOL PopupMenu::setMenuItemInfo(HMENU hmenu, UINT item, LPMENUITEMINFOW info)
{
	return SetMenuItemInfo(hmenu, item, false, info);
}

BOOL PopupMenu::deleteMenu(HMENU hmenu, UINT item)
{
	return DeleteMenu(hmenu, item, MF_BYCOMMAND);
}

BOOL PopupMenu::insertMenu(HMENU hmenu, UINT item, UINT flags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
	return InsertMenu(hmenu, item, MF_BYCOMMAND | flags, uIDNewItem, lpNewItem);
}

PopupMenu::PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout)
{
	int index{};
	if (m_xamlMenu = xamlMenuFlyout.try_as<winrt::WinUI3Package::PopupMenuFlyout>())
		appendMenu(m_xamlMenu.Items(), m_menu, index);
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
		m_themeListenerToken = ThemeListener::Add([this]() {
			auto const dpi = Utils::GetPrimaryMonitorDpi();
			redrawMenuIcon(
				m_menu,
				m_xamlMenu.Items(),
				dpi,
				ThemeSettingsImpl::AppsUseLightTheme() ? winrt::Microsoft::UI::Xaml::ApplicationTheme::Light : winrt::Microsoft::UI::Xaml::ApplicationTheme::Dark
			);
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
 	winrt::get_self<winrt::WinUI3Package::implementation::PopupMenuFlyoutItem>(m_menuItemCache[index].as<winrt::WinUI3Package::PopupMenuFlyoutItem>())->m_clickEvent(m_menuItemCache[index], nullptr);
}
