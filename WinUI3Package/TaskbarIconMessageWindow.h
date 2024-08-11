#pragma once

#include <vector>

class TaskbarIconBase;
class TaskbarIconMessageWindow
{
	constexpr static auto TaskbarIconWindowClass = L"MiLineNotifyIcon";

	static void registerIfNeeded();
	static LRESULT windowProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	HWND m_hwnd;
	TaskbarIconBase* m_icon;
public:
	TaskbarIconMessageWindow(TaskbarIconBase& icon);
	~TaskbarIconMessageWindow();
	HWND Get();
};
