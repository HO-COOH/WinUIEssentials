#pragma once

class TaskbarIconBase;
class TaskbarIconMessageWindow
{
	constexpr static auto TaskbarIconWindowClass = L"MiLineNotifyIcon";
	constexpr static UINT_PTR DoubleClickTimerId = 0x102;

	static void registerIfNeeded();
	static LRESULT windowProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	HWND m_hwnd;
	TaskbarIconBase* m_icon;
	bool doubleClickTimerStarted{};
	bool doubleClicked{};

	void setTimer();
	void destroyTimer();
public:
	TaskbarIconMessageWindow(TaskbarIconBase& icon);
	~TaskbarIconMessageWindow();
	HWND Get();
};
