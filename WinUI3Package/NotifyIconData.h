#pragma once
#include <Windows.h>
#include <shellapi.h>
#include <cassert>
#include <string_view>
#pragma comment(lib, "shell32.lib")

/**
 * @brief Wrapper for win32 `NOTIFYICONDATAW`
 */
class NotifyIconData
{
	NOTIFYICONDATA m_data
	{
		.cbSize = sizeof(m_data),
		.uVersion = NOTIFYICON_VERSION
	};

	void assertId()
	{
#if defined (_DEBUG) || defined (DEBUG)
		bool const useHwndWithId = (m_data.hWnd != HWND{} && m_data.uID != UINT{});
		bool const useGuid = (m_data.guidItem != GUID{});
		assert(
			(useHwndWithId && !useGuid) ||
			(!useHwndWithId && useGuid)
		);
#endif
	}
public:
	constexpr NotifyIconData& hWnd(HWND value)
	{
		m_data.hWnd = value;
		return *this;
	}

	constexpr NotifyIconData& uID(UINT value)
	{
		m_data.uID = value;
		return *this;
	}

	constexpr NotifyIconData& uCallbackMessage(UINT value)
	{
		m_data.uCallbackMessage = value;
		m_data.uFlags |= NIF_MESSAGE;
		return *this;
	}

	constexpr NotifyIconData& hIcon(HICON value)
	{
		m_data.hIcon = value;
		m_data.uFlags |= NIF_ICON;
		return *this;
	}

	constexpr NotifyIconData& szTip(std::wstring_view value)
	{
		assert(value.size() <= std::size(m_data.szTip) - 1);
		std::ranges::copy(value, m_data.szTip);
		m_data.uFlags |= NIF_TIP;
		return *this;
	}

	constexpr NotifyIconData& guidItem(GUID const& value)
	{
		m_data.guidItem = value;
		m_data.uFlags |= NIF_GUID;
		return *this;
	}

	constexpr NotifyIconData& szInfoTitle(std::wstring_view value)
	{
		assert(value.size() <= std::size(m_data.szInfoTitle) - 1);
		std::ranges::copy(value, m_data.szInfoTitle);
		m_data.uFlags |= NIF_INFO;
		return *this;
	}

	constexpr NotifyIconData& dwInfoFlags(DWORD value)
	{
		m_data.dwInfoFlags = value;
		return *this;
	}

	constexpr NotifyIconData& hBalloonIcon(HICON value)
	{
		m_data.hBalloonIcon = value;
		m_data.dwInfoFlags |= NIIF_USER;
		return *this;
	}

	void Add()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_ADD, &m_data));
	}

	void Modify()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_MODIFY, &m_data));
	}

	void Delete()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_DELETE, &m_data));
	}

	void SetFocus()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_SETFOCUS, &m_data));
	}

	void SetVersion()
	{
		winrt::check_bool(Shell_NotifyIcon(NIM_SETVERSION, &m_data));
	}
};
