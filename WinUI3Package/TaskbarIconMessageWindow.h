#pragma once
#include "TaskbarIconBase.h"
#include <vector>
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
	static HWND s_instance;
public:
	static HWND Get();

	static inline std::vector<TaskbarIconBase*> s_icons;
};
