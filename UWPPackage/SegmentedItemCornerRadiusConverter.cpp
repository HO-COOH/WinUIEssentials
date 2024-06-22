#include "pch.h"
#include "SegmentedItemCornerRadiusConverter.h"
#if __has_include("SegmentedItemCornerRadiusConverter.g.cpp")
#include "SegmentedItemCornerRadiusConverter.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::CornerRadius SegmentedItemCornerRadiusConverter::SegmentedCornerRadius()
	{
		return m_cornerRadius;
	}

	void SegmentedItemCornerRadiusConverter::SegmentedCornerRadius(winrt::Windows::UI::Xaml::CornerRadius value)
	{
		m_cornerRadius = value;
		m_set = true;
	}

	winrt::Windows::Foundation::IInspectable SegmentedItemCornerRadiusConverter::Convert(
		winrt::Windows::Foundation::IInspectable const& value,
		winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
		winrt::Windows::Foundation::IInspectable const& parameter,
		winrt::hstring const& language)
	{
		if (!m_set)
			m_cornerRadius = value.as<UWPPackage::Segmented>().CornerRadius();
		auto segmentedItem = value.as<UWPPackage::SegmentedItem>();
		auto listView = winrt::Windows::UI::Xaml::Controls::ItemsControl::ItemsControlFromItemContainer(segmentedItem);
		auto const index = listView.IndexFromContainer(segmentedItem);
		auto items = listView.Items();
		auto const numItems = items.Size();

		if (numItems == 1)
		{
			return winrt::box_value(m_cornerRadius);
		}
		else
		{
			// >= 2 items
			//auto const isHorizontalLayout = (
			//	items.GetAt(0).as<winrt::Windows::UI::Xaml::FrameworkElement>().ActualOffset().x ==
			//	items.GetAt(1).as<winrt::Windows::UI::Xaml::FrameworkElement>().ActualOffset().x
			//);

			auto const isHorizontalLayout = SegmentedItemCornerRadiusConverter::isHorizontalLayout(listView.ItemsPanelRoot());

			auto result = m_cornerRadius;
			if (isHorizontalLayout)
			{
				/*
							╭----╷----╷----╮
							|    |    |    |
							╰----╵----╵----╯
				*/
				if (index == 0)
				{
					result.TopRight = 0;
					result.BottomRight = 0;
				}
				else if (index == numItems - 1)
				{
					result.TopLeft = 0;
					result.BottomLeft = 0;
				}
				else
				{
					result = {};
				}
			}
			else
			{
				/*
							╭----╮
							|    |
							|----|
							|    |
							|----|
							|    |
							╰----╯
				*/
				if (index == 0)
				{
					result.BottomLeft = 0;
					result.BottomRight = 0;
				}
				else if (index == numItems - 1)
				{
					result.TopLeft = 0;
					result.TopRight = 0;
				}
				else
				{
					result = {};
				}
			}
			return winrt::box_value(result);

		}
		return winrt::box_value(m_cornerRadius);
	}

	winrt::Windows::Foundation::IInspectable SegmentedItemCornerRadiusConverter::ConvertBack(
		winrt::Windows::Foundation::IInspectable const& value,
		winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
		winrt::Windows::Foundation::IInspectable const& parameter,
		winrt::hstring const& language)
	{
		return value;
	}
	bool SegmentedItemCornerRadiusConverter::isHorizontalLayout(winrt::Windows::UI::Xaml::Controls::Panel const& panel)
	{
		if (auto stackPanel = panel.try_as<winrt::Windows::UI::Xaml::Controls::StackPanel>())
		{
			return stackPanel.Orientation() == winrt::Windows::UI::Xaml::Controls::Orientation::Horizontal;
		}
		else if (auto equalPanel = panel.try_as<UWPPackage::EqualPanel>())
		{
			return equalPanel.Orientation() == winrt::Windows::UI::Xaml::Controls::Orientation::Horizontal;
		}
		return true;
	}
}
