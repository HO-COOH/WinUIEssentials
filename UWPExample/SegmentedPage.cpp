#include "pch.h"
#include "SegmentedPage.h"
#if __has_include("SegmentedPage.g.cpp")
#include "SegmentedPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<SegmentedPage> s_tags{ L"segmented", L"button", L"control" };
}
