#pragma once
#include "NotifyIconData.h"
#include <string_view>
#include <functional>
#include "PopupMenu.h"
#include "MenuFlyoutWrapper.h"
#include <variant>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "TaskbarIconMessageWindow.h"
class TaskbarIconBase
{
protected:
	NotifyIconData m_iconData;
	std::variant<std::monostate, MenuFlyoutWrapper, PopupMenu> m_menu;
	TaskbarIconMessageWindow m_messageWindow;
public:
	TaskbarIconBase();

	constexpr static UINT CallbackMessage = 0x1001;

	TaskbarIconBase& ToolTip(std::wstring_view value);
	
	void Show();
	void Remove();

	template<typename MenuType>
	void SetMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenu)
	{
		m_menu.emplace<MenuType>(xamlMenu);
	}

	void OnWM_CONTEXTMENU(WPARAM wparam, LPARAM lparam);
	void OnWM_COMMAND(WPARAM wparam, LPARAM lparam);
	
	~TaskbarIconBase();
};
