#include "pch.h"
#include "NamedUrl.h"
#if __has_include("NamedUrl.g.cpp")
#include "NamedUrl.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	winrt::hstring NamedUrl::Name()
	{
		return m_name;
	}

	void NamedUrl::Name(winrt::hstring const& value)
	{
		m_name = value;
	}

	winrt::Windows::Foundation::Uri NamedUrl::Url()
	{
		return m_url;
	}

	void NamedUrl::Url(winrt::Windows::Foundation::Uri const& value)
	{
		m_url = value;
	}
}
