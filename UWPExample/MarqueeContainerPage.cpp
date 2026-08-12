#include "pch.h"
#include "MarqueeContainerPage.h"
#if __has_include("MarqueeContainerPage.g.cpp")
#include "MarqueeContainerPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<MarqueeContainerPage> s_tags{ L"marqueetext", L"marquee", L"textblock", L"text", L"container", L"control" };
}
