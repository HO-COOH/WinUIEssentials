#include "pch.h"
#include "ConvertersPage.h"
#if __has_include("ConvertersPage.g.cpp")
#include "ConvertersPage.g.cpp"
#endif
#include "PageTagRegister.h"

namespace winrt::UWPExample::implementation
{
	static PageTagRegister<ConvertersPage> s_tags{ L"converter", L"convert", L"ivalueconverter", L"binding" };
}
