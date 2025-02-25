#include "pch.h"
#include "TaskbarIconMessageWindow.h"
#include "TaskbarIconBase.h"
#include "TaskbarIconXamlEvents.h"

void TaskbarIconMessageWindow::registerIfNeeded()
{
	static bool registered = false;

	if (registered)
		return;

	WNDCLASS windowClass 
	{
		.style = CS_DBLCLKS,
		.lpfnWndProc = &TaskbarIconMessageWindow::windowProc,
		.cbWndExtra = sizeof(void*),
		.lpszClassName = TaskbarIconWindowClass,
	};
	RegisterClass(&windowClass);
}


LRESULT TaskbarIconMessageWindow::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_TIMER:
	{
		auto thisPtr = reinterpret_cast<TaskbarIconMessageWindow*>(GetWindowLongPtr(hwnd, 0));
		assert(wparam == DoubleClickTimerId);
		if (thisPtr->doubleClickTimerStarted && !thisPtr->doubleClicked)
		{
			thisPtr->doubleClickTimerStarted = false;
			thisPtr->doubleClicked = false;
			if (thisPtr->m_icon->m_ptrXamlEvents)
				thisPtr->m_icon->m_ptrXamlEvents->m_leftPressed();
			thisPtr->destroyTimer();
			break;
		}
		break;
	}
	case TaskbarIconBase::CallbackMessage:
	{
		auto thisPtr = getThisPointer(hwnd);
		switch(LOWORD(lparam))
		{
		case WM_LBUTTONUP:
			if (!thisPtr->doubleClickTimerStarted)
			{
				thisPtr->setTimer();
				thisPtr->doubleClickTimerStarted = true;
			}
			break;
		case WM_MOUSEHOVER:
			if (thisPtr->m_icon->m_ptrXamlEvents)
				thisPtr->m_icon->m_ptrXamlEvents->m_pointerHover();
			break;
		case WM_LBUTTONDBLCLK:
			thisPtr->doubleClicked = true;
			if (thisPtr->m_icon->m_ptrXamlEvents)
				thisPtr->m_icon->m_ptrXamlEvents->m_leftDoublePressed();
			break;
		case WM_RBUTTONUP:
			if (thisPtr->m_icon->m_ptrXamlEvents)
				thisPtr->m_icon->m_ptrXamlEvents->m_rightPressed();
			break;
		case NIN_POPUPOPEN:
			if (thisPtr->m_icon->m_ptrXamlEvents)
				thisPtr->m_icon->m_ptrXamlEvents->m_pointerHover();
			break;
		case WM_CONTEXTMENU:
			winrt::check_bool(SetForegroundWindow(hwnd));
			thisPtr->m_icon->OnWM_CONTEXTMENU(wparam, lparam);
			break;
		}
		return 0;
	}
	case WM_COMMAND:
		getThisPointer(hwnd)->m_icon->OnWM_COMMAND(wparam, lparam);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void TaskbarIconMessageWindow::setTimer()
{
	SetTimer(m_hwnd, DoubleClickTimerId, min(GetDoubleClickTime(), DoubleClickMaxThreshold), nullptr);
}

void TaskbarIconMessageWindow::destroyTimer()
{
	winrt::check_bool(KillTimer(m_hwnd, DoubleClickTimerId));
}

TaskbarIconMessageWindow* TaskbarIconMessageWindow::getThisPointer(HWND hwnd)
{
	return reinterpret_cast<TaskbarIconMessageWindow*>(GetWindowLongPtr(hwnd, 0));
}

TaskbarIconMessageWindow::TaskbarIconMessageWindow(TaskbarIconBase& icon) : m_icon{&icon}
{
	registerIfNeeded();
	winrt::check_pointer(m_hwnd = CreateWindowEx(
		0,
		TaskbarIconWindowClass,
		TaskbarIconWindowClass,
		0,
		0,
		0,
		0,
		0,
		NULL,
		NULL,
		NULL,
		NULL
	));
	SetWindowLongPtr(m_hwnd, 0, reinterpret_cast<LONG_PTR>(this));
}

TaskbarIconMessageWindow::~TaskbarIconMessageWindow()
{
	winrt::check_bool(DestroyWindow(m_hwnd));
}

HWND TaskbarIconMessageWindow::Get()
{
	return m_hwnd;
}
