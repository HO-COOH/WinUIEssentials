#include "pch.h"
#include "SegmentedPage.h"
#if __has_include("SegmentedPage.g.cpp")
#include "SegmentedPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::WinUI3Example::implementation
{
    static PageTagRegister<SegmentedPage> s_tags{ L"segmented", L"segmenteditem", L"button", L"control" };
}
