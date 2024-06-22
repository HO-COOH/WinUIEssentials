#include "pch.h"
#include "GroupBox.h"
#if __has_include("GroupBox.g.cpp")
#include "GroupBox.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Windows::Foundation::IInspectable GroupBox::Header()
	{
		return m_header;
	}
	void GroupBox::Header(winrt::Windows::Foundation::IInspectable value)
	{
		m_header = value;
	}
}
