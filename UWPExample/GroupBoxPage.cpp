#include "pch.h"
#include "GroupBoxPage.h"
#if __has_include("GroupBoxPage.g.cpp")
#include "GroupBoxPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<GroupBoxPage> s_tags{ L"groupbox", L"win32", L"control" };
}
