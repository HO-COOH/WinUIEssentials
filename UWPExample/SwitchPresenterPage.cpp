#include "pch.h"
#include "SwitchPresenterPage.h"
#if __has_include("SwitchPresenterPage.g.cpp")
#include "SwitchPresenterPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<SwitchPresenterPage> s_tags{ L"switchpresenter", L"control" };
}
