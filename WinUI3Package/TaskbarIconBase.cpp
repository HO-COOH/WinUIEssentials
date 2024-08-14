#include "pch.h"
#include "TaskbarIconBase.h"
#include "GuidWrapper.h"
#include "TaskbarIconMessageWindow.h"
#include <windowsx.h>

PopupMenu& TaskbarIconBase::getPopupMenu()
{
	return std::get<2>(m_menu);
}

TaskbarIconBase::TaskbarIconBase() : m_messageWindow{*this}
{
	m_iconData.guidItem(GuidWrapper{});
	m_iconData.hWnd(m_messageWindow.Get());
}

TaskbarIconBase& TaskbarIconBase::ToolTip(std::wstring_view value)
{
	m_iconData.szTip(value);
	return *this;
}

void TaskbarIconBase::Show()
{
	m_iconData.uCallbackMessage(CallbackMessage);
	m_iconData.Add();
}

void TaskbarIconBase::Remove()
{
	m_iconData.Delete();
}

void TaskbarIconBase::SetEvents(TaskbarIconXamlEvents& events)
{
	m_ptrXamlEvents = &events;
}

void TaskbarIconBase::SetTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme)
{
	m_theme = theme;
}

void TaskbarIconBase::OnWM_CONTEXTMENU(WPARAM wparam, LPARAM lparam)
{
	std::visit([wparam, lparam, this](auto&& menu) {
		using MenuType = std::remove_reference_t<decltype(menu)>;
		if constexpr (std::is_same_v<MenuType, PopupMenu>)
		{
			menu.Show({ GET_X_LPARAM(wparam), GET_Y_LPARAM(wparam) }, m_messageWindow.Get());
		}
		else if constexpr (std::is_same_v<MenuType, MenuFlyoutWrapper>)
		{
			menu.Show({ GET_X_LPARAM(wparam), GET_Y_LPARAM(wparam) });
		}
	}, m_menu);

}

void TaskbarIconBase::OnWM_COMMAND(WPARAM wparam, LPARAM lparam)
{
	auto const highWord = HIWORD(wparam);
	assert(highWord == 0);
	auto const id = LOWORD(wparam);
	getPopupMenu().OnMenuClick(id);
}

TaskbarIconBase::~TaskbarIconBase()
{
	Remove();
}
