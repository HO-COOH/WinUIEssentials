#include "pch.h"
#include "TogglePopupMenuFlyoutItem.h"
#include "PopupMenuFlyoutItem.h"
#include "PopupMenuFlyoutItem.g.h"
#if __has_include("TogglePopupMenuFlyoutItem.g.cpp")
#include "TogglePopupMenuFlyoutItem.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty TogglePopupMenuFlyoutItem::s_isCheckedProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"IsChecked",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::WinUI3Package::PopupMenuFlyoutItemType TogglePopupMenuFlyoutItem::Type()
	{
		return winrt::WinUI3Package::PopupMenuFlyoutItemType::ToggleItem;
	}

	bool TogglePopupMenuFlyoutItem::IsChecked()
	{
		return winrt::unbox_value<bool>(GetValue(IsCheckedProperty()));
	}
	void TogglePopupMenuFlyoutItem::IsChecked(bool value)
	{
		SetValue(IsCheckedProperty(), winrt::box_value(value));
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty TogglePopupMenuFlyoutItem::IsCheckedProperty()
	{
		return s_isCheckedProperty;
	}
}
