#pragma once
#include <shellapi.h>
class TaskbarIconBase;
class TaskbarIconMessageWindow
{
	constexpr static auto TaskbarIconWindowClass = L"WinUIEssentialNotifyIcon";
	constexpr static UINT_PTR DoubleClickTimerId = 0x102;
	constexpr static UINT_PTR MouseMoveTimerId = 0x103;
	constexpr static auto DoubleClickMaxThreshold = 500;
	constexpr static auto MouseMoveTimerInterval = 100;

	static void registerIfNeeded();
	static LRESULT CALLBACK windowProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	HWND m_hwnd;
	TaskbarIconBase* m_icon;
	bool doubleClickTimerStarted{};
	bool doubleClicked{};
	bool mouseInIcon{};

	static void setDoubleClickTimer(HWND hwnd);
	static void killDoubleClickTimer(HWND hwnd);

	static void setMouseMoveTimer(HWND hwnd);
	static void killMouseMoveTimer(HWND hwnd);

	//Return a this pointer from this message window's hwnd
	static TaskbarIconMessageWindow* getThisPointer(HWND hwnd);
	NOTIFYICONIDENTIFIER getIdentifier() const;
public:
	TaskbarIconMessageWindow(TaskbarIconBase& icon);
	~TaskbarIconMessageWindow();
	HWND Get() const;
};
