#pragma once
#include <winrt/WinUI3Package.h>

template<typename Derived>
class ITableDataBase
{
	winrt::event<winrt::Windows::Foundation::EventHandler<winrt::WinUI3Package::UpdateRowDataEventArgs>> m_updateRowData;
public:

	winrt::event_token UpdateRowData(winrt::Windows::Foundation::EventHandler<winrt::WinUI3Package::UpdateRowDataEventArgs> const& handler)
	{
		return m_updateRowData.add(handler);
	}

	void UpdateRowData(winrt::event_token const& token) noexcept
	{
		m_updateRowData.remove(token);
	}
};