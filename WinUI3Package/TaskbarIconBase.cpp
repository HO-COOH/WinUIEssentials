#include "pch.h"
#include "TaskbarIconBase.h"
#include "GuidWrapper.h"
#include "TaskbarIconMessageWindow.h"
#include <windowsx.h>
#include "InvalidXamlMenuFlyoutTypeError.hpp"

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

TaskbarIconBase& TaskbarIconBase::Guid(winrt::guid value)
{
	m_iconData.guidItem(value);
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

void TaskbarIconBase::SetMenu(winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase const& xamlMenu)
{
	if (m_menu.index() != 0)
		return;

	if (auto xamlMenuFlyout = xamlMenu.try_as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyout>())
		m_menu.emplace<MenuFlyoutWrapper>(xamlMenuFlyout).Theme(m_theme);
	else if (auto popupMenuFlyout = xamlMenu.try_as<winrt::WinUI3Package::PopupMenuFlyout>())
		m_menu.emplace<PopupMenu>(popupMenuFlyout).Theme(m_theme);
	else
		throw InvalidXamlMenuFlyoutTypeError{};
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
