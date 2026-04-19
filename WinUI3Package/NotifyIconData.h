#pragma once
#include <Windows.h>
#include <shellapi.h>
#include <cassert>
#include <string_view>
#pragma comment(lib, "shell32.lib")

/**
 * @brief Wrapper for win32 `NOTIFYICONDATAW`
 */
struct NotifyIconData : private NOTIFYICONDATA
{
	constexpr NotifyIconData()
	{
		cbSize = sizeof(NOTIFYICONDATA);
		uVersion = NOTIFYICON_VERSION;
	}

	constexpr NotifyIconData& hWnd(HWND value)
	{
		NOTIFYICONDATA::hWnd = value;
		return *this;
	}

	constexpr NotifyIconData& uID(UINT value)
	{
		NOTIFYICONDATA::uID = value;
		return *this;
	}

	constexpr NotifyIconData& uCallbackMessage(UINT value)
	{
		NOTIFYICONDATA::uCallbackMessage = value;
		NOTIFYICONDATA::uFlags |= NIF_MESSAGE;
		return *this;
	}

	constexpr NotifyIconData& hIcon(HICON value)
	{
		NOTIFYICONDATA::hIcon = value;
		NOTIFYICONDATA::uFlags |= NIF_ICON;
		return *this;
	}

	constexpr NotifyIconData& szTip(std::wstring_view value)
	{
		assert(value.size() <= std::size(NOTIFYICONDATA::szTip) - 1);
		std::ranges::copy(value, NOTIFYICONDATA::szTip);
		NOTIFYICONDATA::uFlags |= NIF_TIP;
		return *this;
	}

	constexpr NotifyIconData& guidItem(GUID const& value)
	{
		NOTIFYICONDATA::guidItem = value;
		NOTIFYICONDATA::uFlags |= NIF_GUID;
		return *this;
	}

	constexpr GUID guidItem() const
	{
		return NOTIFYICONDATA::guidItem;
	}

	constexpr NotifyIconData& szInfoTitle(std::wstring_view value)
	{
		assert(value.size() <= std::size(NOTIFYICONDATA::szInfoTitle) - 1);
		std::ranges::copy(value, NOTIFYICONDATA::szInfoTitle);
		NOTIFYICONDATA::uFlags |= NIF_INFO;
		return *this;
	}

	constexpr NotifyIconData& dwInfoFlags(DWORD value)
	{
		NOTIFYICONDATA::dwInfoFlags = value;
		return *this;
	}

	constexpr NotifyIconData& hBalloonIcon(HICON value)
	{
		NOTIFYICONDATA::hBalloonIcon = value;
		NOTIFYICONDATA::dwInfoFlags |= NIIF_USER;
		return *this;
	}

	void Add()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_ADD, this));
	}

	void Modify()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_MODIFY, this));
	}

	void Delete()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_DELETE, this));
	}

	void SetFocus()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_SETFOCUS, this));
	}

	void SetVersion()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_SETVERSION, this));
	}
};
