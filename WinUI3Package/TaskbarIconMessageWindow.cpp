#include "pch.h"
#include "TaskbarIconMessageWindow.h"

void TaskbarIconMessageWindow::registerIfNeeded()
{
	static bool registered = false;

	if (registered)
		return;

	WNDCLASS windowClass 
	{
		.lpfnWndProc = &TaskbarIconMessageWindow::windowProc,
		.lpszClassName = TaskbarIconWindowClass,
	};
	RegisterClass(&windowClass);
}

HWND TaskbarIconMessageWindow::s_instance;

LRESULT TaskbarIconMessageWindow::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

HWND TaskbarIconMessageWindow::Get()
{
	if (s_instance != HWND{})
		return s_instance;

	registerIfNeeded();
	s_instance = CreateWindowEx(
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
	);
	winrt::check_pointer(s_instance);
	return s_instance;
}
