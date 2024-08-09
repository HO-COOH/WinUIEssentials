#include "pch.h"
#include "PopupMenu.h"
#include "TaskbarIconMessageWindow.h"
#include "MenuFlyoutItemBaseVisitor.hpp"

#if __has_include("winrt/Microsoft.UI.Xaml.Controls.h")
void PopupMenu::appendMenu(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItemBase> xamlMenu, HMENU menu)
{
	ForEachMenuItem(xamlMenu,
		[this, menu](winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem const& item)
		{
			winrt::check_bool(AppendMenu(
				menu,
				NULL,
				NULL,
				item.Text().data()
			));
			if (auto command = item.Command())
			{
				m_menuItemCommandRevoker.push_back(item.Click(winrt::auto_revoke, [command, parameter = item.CommandParameter()](auto&&...) {
					command.Execute(parameter);
				}));
			}
		},
		[this, menu](winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSeparator const& separator)
		{
			winrt::check_bool(AppendMenu(
				menu,
				MF_SEPARATOR,
				NULL,
				NULL
			));
		},
		[this, menu](winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutSubItem const& subItem)
		{
			auto subMenu = CreatePopupMenu();
			winrt::check_bool(AppendMenu(menu, MF_POPUP, reinterpret_cast<UINT_PTR>(subMenu), subItem.Text().data()));
			appendMenu(subItem.Items(), subMenu);
		},

		[this, menu](winrt::Microsoft::UI::Xaml::Controls::ToggleMenuFlyoutItem const& toggleItem)
		{
			winrt::check_bool(AppendMenu(
				menu,
				toggleItem.IsChecked() ? MF_CHECKED : MF_UNCHECKED,
				NULL,
				toggleItem.Text().data()
			));

			if (auto command = toggleItem.Command())
			{
				m_menuItemCommandRevoker.push_back(toggleItem.Click(winrt::auto_revoke, [command, parameter = toggleItem.CommandParameter()](auto&&...) {
					command.Execute(parameter);
					}));
			}
		});
}

PopupMenu::PopupMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenuFlyout)
{
	appendMenu(xamlMenuFlyout.Items(), m_menu);
}
#endif

PopupMenu::~PopupMenu()
{
	winrt::check_bool(DestroyMenu(m_menu));
}

void PopupMenu::Show(POINT pt)
{


	/*test*/
	//MENUITEMINFO info{ .cbSize = sizeof(info), .fMask = MIIM_DATA | MIIM_CHECKMARKS | MIIM_TYPE };
	//winrt::check_bool(GetMenuItemInfo(m_menu, 1, true, &info));
	//info.dwItemData = reinterpret_cast<ULONG_PTR>(L"Changed item");
	//winrt::check_bool(SetMenuItemInfo(m_menu, 1, true, &info));

	TrackPopupMenuEx(
		m_menu,
		TPM_LEFTALIGN,
		pt.x,
		pt.y,
		TaskbarIconMessageWindow::Get(),
		nullptr
	);

}
