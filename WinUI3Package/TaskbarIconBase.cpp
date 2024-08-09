#include "pch.h"
#include "TaskbarIconBase.h"
#include "GuidWrapper.h"
#include "TaskbarIconMessageWindow.h"
#include <windowsx.h>

TaskbarIconBase::TaskbarIconBase()
{
	m_iconData.guidItem(GuidWrapper{});
	m_iconData.hWnd(TaskbarIconMessageWindow::Get());
}

TaskbarIconBase& TaskbarIconBase::ToolTip(std::wstring_view value)
{
	m_iconData.szTip(value);
	return *this;
}

void TaskbarIconBase::Show()
{
	m_iconData.uCallbackMessage(0x1001);
	m_iconData.Add();
}

void TaskbarIconBase::Remove()
{
	m_iconData.Delete();
}

void TaskbarIconBase::SetMenu(winrt::Microsoft::UI::Xaml::Controls::MenuFlyout const& xamlMenu)
{
	m_menu.emplace<2>(xamlMenu);
	f = [this](WPARAM wparam, LPARAM lparam)
		{
			std::get<2>(m_menu).Show({ GET_X_LPARAM(wparam), GET_Y_LPARAM(wparam) });
		};
	TaskbarIconMessageWindow::s_icons.push_back(this);
}

TaskbarIconBase::~TaskbarIconBase()
{
	Remove();
}
