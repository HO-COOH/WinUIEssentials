#include "pch.h"
#include "TaskbarIconBase.h"
#include "GuidWrapper.h"
#include "TaskbarIconMessageWindow.h"

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
	m_iconData.Add();
}

void TaskbarIconBase::Remove()
{
	m_iconData.Delete();
}

TaskbarIconBase::~TaskbarIconBase()
{
	Remove();
}
