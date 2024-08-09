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
		.lpszClassName = TaskbarIconWindowClass,
	};
	RegisterClass(&windowClass);

	wil::unique_hmodule hUxTheme{ LoadLibraryEx(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32) };
	auto fnSetPreferredAppMode = reinterpret_cast<FnSetPreferredAppMode>(GetProcAddress(hUxTheme.get(), MAKEINTRESOURCEA(135)));
	fnSetPreferredAppMode(PreferredAppMode::ForceDark);
}

HWND TaskbarIconMessageWindow::s_instance;



LRESULT TaskbarIconMessageWindow::windowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == 0x1001 && LOWORD(lparam) == WM_CONTEXTMENU)
	{
		SetForegroundWindow(Get());
		for (auto icon : s_icons)
		{
			icon->f(wparam, lparam);
		}
		return 0;
	}
	else if (msg == WM_COMMAND)
	{
		OutputDebugString(L"Command\n");
	}
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
