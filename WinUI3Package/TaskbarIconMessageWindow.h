#pragma once
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
};
