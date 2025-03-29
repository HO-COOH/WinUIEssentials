#include "pch.h"
#include "FontInfo.h"
#if __has_include("FontInfo.g.cpp")
#include "FontInfo.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	FontInfo::FontInfo(
		winrt::hstring const& name, 
		winrt::Microsoft::UI::Xaml::Media::FontFamily const& font) :
		m_name{name}, m_font{font}
	{
	}

	winrt::hstring FontInfo::Name()
	{
		return m_name;
	}

	winrt::Microsoft::UI::Xaml::Media::FontFamily FontInfo::Font()
	{
		return m_font;
	}
}
