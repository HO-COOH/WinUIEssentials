#include "pch.h"
#include "PhotoDataItemWithDimension.h"
#if __has_include("PhotoDataItemWithDimension.g.cpp")
#include "PhotoDataItemWithDimension.g.cpp"
#endif

namespace winrt::WinUI3Example::implementation
{
	double PhotoDataItemWithDimension::Width()
	{
		return m_width;
	}

	void PhotoDataItemWithDimension::Width(double value)
	{
		m_width = value;
	}

	double PhotoDataItemWithDimension::Height()
	{
		return m_height;
	}

	void PhotoDataItemWithDimension::Height(double value)
	{
		m_height = value;
	}

	winrt::hstring PhotoDataItemWithDimension::Title()
	{
		return m_title;
	}

	void PhotoDataItemWithDimension::Title(winrt::hstring const& value)
	{
		m_title = value;
	}

	winrt::hstring PhotoDataItemWithDimension::Category()
	{
		return m_category;
	}

	void PhotoDataItemWithDimension::Category(winrt::hstring const& value)
	{
		m_category = value;
	}

	winrt::hstring PhotoDataItemWithDimension::Thumbnail()
	{
		return m_thumbnail;
	}

	void PhotoDataItemWithDimension::Thumbnail(winrt::hstring const& value)
	{
		m_thumbnail = value;
	}
}
