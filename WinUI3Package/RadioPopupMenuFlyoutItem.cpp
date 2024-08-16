#include "pch.h"
#include "RadioPopupMenuFlyoutItem.h"
#if __has_include("RadioPopupMenuFlyoutItem.g.cpp")
#include "RadioPopupMenuFlyoutItem.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty RadioPopupMenuFlyoutItem::s_isCheckedProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsChecked",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty RadioPopupMenuFlyoutItem::s_groupNameProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"GroupName",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::WinUI3Package::PopupMenuFlyoutItemType RadioPopupMenuFlyoutItem::Type()
	{
		return winrt::WinUI3Package::PopupMenuFlyoutItemType::RadioItem;
	}
	bool RadioPopupMenuFlyoutItem::IsChecked()
	{
		return false;
	}
	void RadioPopupMenuFlyoutItem::IsChecked(bool value)
	{
	}
	winrt::hstring RadioPopupMenuFlyoutItem::GroupName()
	{
		return winrt::hstring();
	}
	void RadioPopupMenuFlyoutItem::GroupName(winrt::hstring const& value)
	{
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty RadioPopupMenuFlyoutItem::IsCheckedProperty()
	{
		return s_isCheckedProperty;
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty RadioPopupMenuFlyoutItem::GroupNameProperty()
	{
		return s_groupNameProperty;
	}
}
