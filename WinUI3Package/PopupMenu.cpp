#include "pch.h"
#include "PopupMenu.h"
#include "TaskbarIconMessageWindow.h"

#include "MenuFlyoutItemBaseVisitor.hpp"
#include "IconUtils.h"
#include "AppsUseLightTheme.h"
#include "InvalidMenuItemIconTypeError.hpp"

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
			winrt::check_bool(AppendMenu(
				menu,
				NULL,
				index,
				flyoutItem.Text().data()
			));

			if (auto icon = flyoutItem.Icon())
			{
				if (auto symbolIcon = icon.try_as<winrt::Microsoft::UI::Xaml::Controls::SymbolIcon>())
				{
					auto symbol = symbolIcon.Symbol();
					MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_FTYPE | MIIM_BITMAP };
					winrt::check_bool(GetMenuItemInfo(menu, index, true, &itemInfo));
					wchar_t s[2]{ static_cast<wchar_t>(symbol) };
					itemInfo.hbmpItem = Utils::DrawGlyph(s, theme, dpi);
					winrt::check_bool(SetMenuItemInfo(menu, index, true, &itemInfo));
				}
				else if (auto fontIcon = icon.try_as<winrt::Microsoft::UI::Xaml::Controls::FontIcon>())
				{
					auto fontFamily = fontIcon.FontFamily().Source();
					auto glyph = fontIcon.Glyph();
					MENUITEMINFO itemInfo{ .cbSize = sizeof(itemInfo), .fMask = MIIM_FTYPE | MIIM_BITMAP };
					winrt::check_bool(GetMenuItemInfo(menu, index, true, &itemInfo));
					itemInfo.hbmpItem = Utils::DrawGlyph(fontFamily, glyph, theme, dpi);
					winrt::check_bool(SetMenuItemInfo(menu, index, true, &itemInfo));
				}
				else
				{
					throw InvalidMenuItemIconTypeError{};
				}
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

PopupMenu::PopupMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenuFlyout)
{
	if (auto menuFlyout = xamlMenuFlyout.try_as<winrt::WinUI3Package::PopupMenuFlyout>())
		appendMenu(menuFlyout.Items(), m_menu);
}
#endif

PopupMenu::~PopupMenu()
{
	winrt::check_bool(DestroyMenu(m_menu));
}

void PopupMenu::Show(POINT pt, HWND ownerHwnd)
{
	TrackPopupMenuEx(
		m_menu,
		TPM_LEFTALIGN,
		pt.x,
		pt.y,
		ownerHwnd,
		nullptr
	);

}

void PopupMenu::OnMenuClick(int index)
{
	//m_commands[index].first.Execute(m_commands[index].second);
}
