#include "pch.h"
#include "PopupMenu.h"
#include "TaskbarIconMessageWindow.h"

#include "MenuFlyoutItemBaseVisitor.hpp"

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
void PopupMenu::appendMenu(winrt::Windows::Foundation::Collections::IVector<winrt::WinUI3Package::PopupMenuFlyoutItemBase> xamlMenu, HMENU menu)
{
	int index{};
	for (auto item : xamlMenu)
	{
		switch (item.Type())
		{
		case winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutItem:
		{
			winrt::check_bool(AppendMenu(
				menu,
				NULL,
				index,
				item.as<winrt::WinUI3Package::PopupMenuFlyoutItem>().Text().data()
			));
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
			assert(false);
			//not yet implemented
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
