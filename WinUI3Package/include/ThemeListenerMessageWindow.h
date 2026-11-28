#pragma once

class ThemeListener;
class ThemeListenerMessageWindow
{
	constexpr static auto ThemeListenerMessageWindowClass = L"ThemeListenerMessageWindow";
	static void registerIfNeeded();

	static LRESULT CALLBACK windowProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);

	HWND m_hwnd;
public:
	ThemeListenerMessageWindow(ThemeListener* listener);
	ThemeListenerMessageWindow(ThemeListenerMessageWindow const&) = delete;
	ThemeListenerMessageWindow(ThemeListenerMessageWindow&&) = delete;
	~ThemeListenerMessageWindow();
};

