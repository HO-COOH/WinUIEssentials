#include "pch.h"
#include "CursorControllerPage.h"
#if __has_include("CursorControllerPage.g.cpp")
#include "CursorControllerPage.g.cpp"
#endif
#include "PageTagRegister.h"
namespace winrt::UWPExample::implementation
{
	static PageTagRegister<CursorControllerPage> s_tags{ L"cursor", L"mouse", L"extension" };
}
