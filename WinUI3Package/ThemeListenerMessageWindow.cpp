#include "pch.h"
#include "ThemeListenerMessageWindow.h"
#include "ThemeListener.h"
#include <winuser.h>

void ThemeListenerMessageWindow::registerIfNeeded()
{
	static bool registered = false;

	if (registered)
		return;

	WNDCLASS windowClass
	{
		.lpfnWndProc = &ThemeListenerMessageWindow::windowProc,
		.lpszClassName = ThemeListenerMessageWindowClass,
	};
	RegisterClass(&windowClass);
}

LRESULT ThemeListenerMessageWindow::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_NCCREATE:
		SetWindowLongPtr(hwnd, GWLP_USERDATA, lparam);
		return true;
	default:
		break;
	}
}

ThemeListenerMessageWindow::ThemeListenerMessageWindow(ThemeListener* listener) : m_hwnd
{
	CreateWindow(
		ThemeListenerMessageWindowClass,
		ThemeListenerMessageWindowClass,
		0,
		0,
		0,
		0,
		0,
		NULL,
		NULL,
		NULL,
		listener
	)
}
{
}

ThemeListenerMessageWindow::~ThemeListenerMessageWindow()
{
	winrt::check_bool(CloseWindow(m_hwnd));
}
