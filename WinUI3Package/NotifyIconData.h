#pragma once
#include <Windows.h>
#include <shellapi.h>
#include <cassert>
#include <string_view>

/**
 * @brief Wrapper for win32 `NOTIFYICONDATAW`
 */
class NotifyIconData
{
	NOTIFYICONDATA m_data
	{
		.cbSize = sizeof(m_data)
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
		wcscpy_s(m_data.szTip, value.data());
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
		wcscpy_s(m_data.szInfoTitle, value.data());
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
};
