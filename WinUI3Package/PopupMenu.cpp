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
				m_commands.size(),
				item.Text().data()
			));
			m_commands.push_back({ item.Command(), item.CommandParameter() });
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
				m_commands.size(),
				toggleItem.Text().data()
			));
			m_commands.push_back({ toggleItem.Command(), toggleItem.CommandParameter() });
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

void PopupMenu::Show(POINT pt, HWND ownerHwnd)
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
		ownerHwnd,
		nullptr
	);

}

void PopupMenu::OnMenuClick(int index)
{
	m_commands[index].first.Execute(m_commands[index].second);
}
