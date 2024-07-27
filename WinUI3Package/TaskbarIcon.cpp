#include "pch.h"
#include "TaskbarIcon.h"
#if __has_include("TaskbarIcon.g.cpp")
#include "TaskbarIcon.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	WinUI3Package::GeneratedIconSource TaskbarIcon::IconSource()
	{
		return m_iconSource;
	}
	void TaskbarIcon::IconSource(WinUI3Package::GeneratedIconSource value)
	{
		m_iconSource = value;
	}
}
