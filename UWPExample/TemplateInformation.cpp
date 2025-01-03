#include "pch.h"
#include "TemplateInformation.h"
#if __has_include("TemplateInformation.g.cpp")
#include "TemplateInformation.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
	winrt::hstring TemplateInformation::Header1()
	{
		return m_header;
	}
	void TemplateInformation::Header1(winrt::hstring const& value)
	{
		m_header = value;
	}
	winrt::hstring TemplateInformation::Regex1()
	{
		return m_regex;
	}
	void TemplateInformation::Regex1(winrt::hstring const& value)
	{
		m_regex = value;
	}
	winrt::hstring TemplateInformation::PlaceholderText1()
	{
		return m_placeholderText;
	}
	void TemplateInformation::PlaceholderText1(winrt::hstring const& value)
	{
		m_placeholderText = value;
	}
}
