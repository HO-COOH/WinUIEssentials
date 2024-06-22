#include "pch.h"
#include "SegmentedMarginConverter.h"
#if __has_include("SegmentedMarginConverter.g.cpp")
#include "SegmentedMarginConverter.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Windows::Foundation::IInspectable SegmentedMarginConverter::Convert(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, winrt::hstring const& language)
	{
		auto segmentedItem = value.as<WinUI3Package::SegmentedItem>();
		auto listView = winrt::Microsoft::UI::Xaml::Controls::ItemsControl::ItemsControlFromItemContainer(segmentedItem);

		auto const index = listView.IndexFromContainer(segmentedItem);

		if (index == 0)
		{
			return winrt::box_value(LeftItemMargin());
		}
		else if (index == listView.Items().Size() - 1)
		{
			return winrt::box_value(RightItemMargin());
		}
		else
			return winrt::box_value(MiddleItemMargin());
	}
	winrt::Windows::Foundation::IInspectable SegmentedMarginConverter::ConvertBack(winrt::Windows::Foundation::IInspectable const& value, winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, winrt::Windows::Foundation::IInspectable const& parameter, winrt::hstring const& language)
	{
		return value;
	}
	winrt::Microsoft::UI::Xaml::Thickness SegmentedMarginConverter::LeftItemMargin()
	{
		return m_leftItemMargin;
	}
	void SegmentedMarginConverter::LeftItemMargin(winrt::Microsoft::UI::Xaml::Thickness value)
	{
		m_leftItemMargin = value;
	}
	winrt::Microsoft::UI::Xaml::Thickness SegmentedMarginConverter::RightItemMargin()
	{
		return m_rightItemMargin;
	}
	void SegmentedMarginConverter::RightItemMargin(winrt::Microsoft::UI::Xaml::Thickness value)
	{
		m_rightItemMargin = value;
	}
	winrt::Microsoft::UI::Xaml::Thickness SegmentedMarginConverter::MiddleItemMargin()
	{
		return m_middleItemMargin;
	}
	void SegmentedMarginConverter::MiddleItemMargin(winrt::Microsoft::UI::Xaml::Thickness value)
	{
		m_middleItemMargin = value;
	}

}
