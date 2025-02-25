#include "pch.h"
#include "ThemeListenerMessageWindow.h"
#include "ThemeListener.h"
#include <winuser.h>

#include "AppsUseLightTheme.h"

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
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(reinterpret_cast<CREATESTRUCT*>(lparam)->lpCreateParams));
		return true;
	case WM_SETTINGCHANGE:
	{
		AppsUseLightTheme const value;
		for (auto& handler : reinterpret_cast<ThemeListener*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))->m_handlers)
			handler(value);
		return true;
	}
	default:
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

ThemeListenerMessageWindow::ThemeListenerMessageWindow(ThemeListener* listener)
{
	registerIfNeeded();
	winrt::check_pointer(m_hwnd = CreateWindow(
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
	));
}

ThemeListenerMessageWindow::~ThemeListenerMessageWindow()
{
	winrt::check_bool(DestroyWindow(m_hwnd));
}
