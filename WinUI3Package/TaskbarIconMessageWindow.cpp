#include "pch.h"
#include "TaskbarIconMessageWindow.h"
#include "TaskbarIconBase.h"
#include <wil/resource.h>

using FnFlushMenuThemes = void(WINAPI*)();
enum PreferredAppMode
{
	Default,
	AllowDark,
	ForceDark,
	ForceLight,
	Max
};

using FnSetPreferredAppMode = PreferredAppMode(WINAPI*)(PreferredAppMode);

void TaskbarIconMessageWindow::registerIfNeeded()
{
	static bool registered = false;

	if (registered)
		return;

	WNDCLASS windowClass 
	{
		.lpfnWndProc = &TaskbarIconMessageWindow::windowProc,
		.cbWndExtra = sizeof(void*),
		.lpszClassName = TaskbarIconWindowClass,
	};
	RegisterClass(&windowClass);

	wil::unique_hmodule hUxTheme{ LoadLibraryEx(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32) };
	auto fnSetPreferredAppMode = reinterpret_cast<FnSetPreferredAppMode>(GetProcAddress(hUxTheme.get(), MAKEINTRESOURCEA(135)));
	fnSetPreferredAppMode(PreferredAppMode::ForceDark);
}


LRESULT TaskbarIconMessageWindow::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case TaskbarIconBase::CallbackMessage:
	{
		auto thisPtr = reinterpret_cast<TaskbarIconBase*>(GetWindowLongPtr(hwnd, 0));
		if (LOWORD(lparam) == WM_CONTEXTMENU)
		{
			thisPtr->OnWM_CONTEXTMENU(wparam, lparam);
		}
		return 0;
	}
	case WM_COMMAND:
		reinterpret_cast<TaskbarIconBase*>(GetWindowLongPtr(hwnd, 0))->OnWM_COMMAND(wparam, lparam);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
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
	SetWindowLongPtr(m_hwnd, 0, reinterpret_cast<LONG_PTR>(m_icon));
}

TaskbarIconMessageWindow::~TaskbarIconMessageWindow()
{
	winrt::check_bool(DestroyWindow(m_hwnd));
}

HWND TaskbarIconMessageWindow::Get()
{
	return m_hwnd;
}
