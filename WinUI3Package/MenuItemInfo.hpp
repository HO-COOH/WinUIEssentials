#pragma once
#include <Windows.h>
#include <string_view>

/**
 * @breif Wrapper for `MENUITEMINFO`
 */
class MenuItemInfo
{
	MENUITEMINFO m_data
	{
		.cbSize = sizeof(m_data)
	};

public:
	constexpr MenuItemInfo& fType(UINT value)
	{
		m_data.fType = value;
		m_data.fMask |= MIIM_FTYPE;
		return *this;
	}

	constexpr MenuItemInfo& fState(UINT value)
	{
		m_data.fState = value;
		m_data.fMask |= MIIM_STATE;
		return *this;
	}

	constexpr MenuItemInfo& wID(UINT value)
	{
		m_data.wID = value;
		m_data.fMask |= MIIM_ID;
		return *this;
	}

	constexpr MenuItemInfo& hSubMenu(HMENU value)
	{
		m_data.hSubMenu = value;
		m_data.fMask |= MIIM_SUBMENU;
		return *this;
	}

	constexpr MenuItemInfo& hbmpChecked(HBITMAP value)
	{
		m_data.hbmpChecked = value;
		m_data.fMask |= MIIM_CHECKMARKS;
		return *this;
	}

	constexpr MenuItemInfo& hbmpUnchecked(HBITMAP value)
	{
		m_data.hbmpUnchecked = value;
		m_data.fMask |= MIIM_CHECKMARKS;
		return *this;
	}

	constexpr MenuItemInfo& dwItemData(ULONG_PTR value)
	{
		m_data.dwItemData = value;
		m_data.fMask |= MIIM_DATA;
		return *this;
	}

	constexpr MenuItemInfo& dwTypeData(std::wstring_view value)
	{
		m_data.dwTypeData = const_cast<LPTSTR>(value.data());
		m_data.cch = value.size();
		m_data.fMask |= MIIM_STRING;
		return *this;
	}

	constexpr MenuItemInfo& hbmpItem(HBITMAP value)
	{
		m_data.hbmpItem = value;
		m_data.fMask |= MIIM_BITMAP;
		return *this;
	}
};