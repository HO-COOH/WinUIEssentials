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
			auto self = getThisPointer(hwnd);
			switch (wparam)
			{
				case DoubleClickTimerId:
					if (self->doubleClickTimerStarted)
					{
						self->doubleClickTimerStarted = false;
						if (!self->doubleClicked)
						{
							if (self->m_icon->m_ptrXamlEvents)
								self->m_icon->m_ptrXamlEvents->m_leftPressed();
						}
					}
					killDoubleClickTimer(hwnd);
					self->doubleClicked = false;
					break;
				case MouseMoveTimerId:
				{
					auto const identifier = self->getIdentifier();
					RECT iconRect;
					Shell_NotifyIconGetRect(&identifier, &iconRect);
					POINT cursorPoint;
					GetCursorPos(&cursorPoint);
					if (!PtInRect(&iconRect, cursorPoint))
					{
						killMouseMoveTimer(hwnd);
						self->mouseInIcon = false;
					}
					break;
				}
				default:
					break;
			}

			break;
		}
		case TaskbarIconBase::CallbackMessage:
		{
			auto self = getThisPointer(hwnd);

			switch(LOWORD(lparam))
			{
				case WM_LBUTTONUP:
					if (!self->doubleClickTimerStarted)
					{
						setDoubleClickTimer(hwnd);
						self->doubleClickTimerStarted = true;
					}
					break;
				case WM_MOUSEMOVE:
					if (!self->mouseInIcon)
					{
						if (self->m_icon->m_ptrXamlEvents)
							self->m_icon->m_ptrXamlEvents->m_pointerHover();
						self->mouseInIcon = true;
						setMouseMoveTimer(hwnd);
					}
					break;
				case WM_LBUTTONDBLCLK:
					self->doubleClicked = true;
					self->doubleClickTimerStarted = false;
					if (self->m_icon->m_ptrXamlEvents)
						self->m_icon->m_ptrXamlEvents->m_leftDoublePressed();
					break;
				case WM_RBUTTONUP:
					if (self->m_icon->m_ptrXamlEvents)
						self->m_icon->m_ptrXamlEvents->m_rightPressed();
					POINT p;
					GetCursorPos(&p);
					winrt::check_bool(SetForegroundWindow(hwnd));
					self->m_icon->OnWM_CONTEXTMENU(MAKELPARAM(p.x, p.y), lparam);
					break;
				case NIN_POPUPOPEN:
					if (self->m_icon->m_ptrXamlEvents)
						self->m_icon->m_ptrXamlEvents->m_pointerHover();
					break;
				case WM_CONTEXTMENU:
					winrt::check_bool(SetForegroundWindow(hwnd));
					self->m_icon->OnWM_CONTEXTMENU(wparam, lparam);
					break;
			}
			break;
		}
		case WM_COMMAND:
			getThisPointer(hwnd)->m_icon->OnWM_COMMAND(wparam, lparam);
			return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void TaskbarIconMessageWindow::setDoubleClickTimer(HWND hwnd)
{
	winrt::check_bool(SetTimer(hwnd, DoubleClickTimerId, min(GetDoubleClickTime(), DoubleClickMaxThreshold), nullptr));
}

void TaskbarIconMessageWindow::killDoubleClickTimer(HWND hwnd)
{
	winrt::check_bool(KillTimer(hwnd, DoubleClickTimerId));
}

void TaskbarIconMessageWindow::setMouseMoveTimer(HWND hwnd)
{
	winrt::check_bool(SetTimer(hwnd, MouseMoveTimerId, MouseMoveTimerInterval, nullptr));
}

void TaskbarIconMessageWindow::killMouseMoveTimer(HWND hwnd)
{
	winrt::check_bool(KillTimer(hwnd, MouseMoveTimerId));
}

TaskbarIconMessageWindow* TaskbarIconMessageWindow::getThisPointer(HWND hwnd)
{
	return reinterpret_cast<TaskbarIconMessageWindow*>(GetWindowLongPtr(hwnd, 0));
}

NOTIFYICONIDENTIFIER TaskbarIconMessageWindow::getIdentifier() const
{
	return NOTIFYICONIDENTIFIER
	{
		.cbSize = sizeof(NOTIFYICONIDENTIFIER),
		.hWnd = m_hwnd,
		.guidItem = m_icon->m_iconData.guidItem(),
	};
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

HWND TaskbarIconMessageWindow::Get() const
{
	return m_hwnd;
}
