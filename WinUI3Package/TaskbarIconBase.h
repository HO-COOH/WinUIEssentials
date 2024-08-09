#pragma once
#include "NotifyIconData.h"
#include <string_view>
#include <functional>
#include "PopupMenu.h"
#include "MenuFlyoutWrapper.h"
#include <variant>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
class TaskbarIconBase
{
protected:
	NotifyIconData m_iconData;
	std::variant<std::monostate, MenuFlyoutWrapper, PopupMenu> m_menu;
public:
	TaskbarIconBase();

	std::function<void(WPARAM, LPARAM)> f;

	TaskbarIconBase& ToolTip(std::wstring_view value);
	
	void Show();
	void Remove();

	void SetMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenu);
	
	~TaskbarIconBase();
};
