#pragma once
#include <winrt/UWPPackage.h>

template<typename Derived>
class ITableDataBase
{
	winrt::event<winrt::Windows::Foundation::EventHandler<winrt::UWPPackage::UpdateRowDataEventArgs>> m_updateRowData;
public:

	winrt::event_token UpdateRowData(winrt::Windows::Foundation::EventHandler<winrt::UWPPackage::UpdateRowDataEventArgs> const& handler)
	{
		return m_updateRowData.add(handler);
	}

	void UpdateRowData(winrt::event_token const& token) noexcept
	{
		m_updateRowData.remove(token);
	}
};