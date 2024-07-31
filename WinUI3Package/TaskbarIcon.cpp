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
	WinUI3Package::GeneratedIconSource TaskbarIcon::LightThemeIconSource()
	{
		return WinUI3Package::GeneratedIconSource();
	}
	void TaskbarIcon::LightThemeIconSource(WinUI3Package::GeneratedIconSource value)
	{
	}
	winrt::Windows::Foundation::Uri TaskbarIcon::LightThemeIcon()
	{
		return winrt::Windows::Foundation::Uri(nullptr);
	}
	void TaskbarIcon::LightThemeIcon(winrt::Windows::Foundation::Uri value)
	{
	}
	WinUI3Package::GeneratedIconSource TaskbarIcon::DarkThemeIconSource()
	{
		return WinUI3Package::GeneratedIconSource();
	}
	void TaskbarIcon::DarkThemeIconSource(WinUI3Package::GeneratedIconSource value)
	{
	}
	winrt::Windows::Foundation::Uri TaskbarIcon::DarkThemeIcon()
	{
		return winrt::Windows::Foundation::Uri(nullptr);
	}
	void TaskbarIcon::DarkThemeIcon(winrt::Windows::Foundation::Uri value)
	{
	}
}
