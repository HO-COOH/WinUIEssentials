#include "pch.h"
#include "SettingsCardPage.h"
#if __has_include("SettingsCardPage.g.cpp")
#include "SettingsCardPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<SettingsCardPage> s_tags{ L"settingscard", L"settings", L"control" };
}
