#include "pch.h"
#include "RadioPopupMenuFlyoutItem.h"
#if __has_include("RadioPopupMenuFlyoutItem.g.cpp")
#include "RadioPopupMenuFlyoutItem.g.cpp"
#endif
#include "PopupMenu.h"

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
		return winrt::unbox_value<bool>(GetValue(IsCheckedProperty()));
	}
	void RadioPopupMenuFlyoutItem::IsChecked(bool value)
	{
		SetValue(IsCheckedProperty(), winrt::box_value(value));

		if (m_parentMenu)
		{
			MENUITEMINFO info
			{
				.cbSize = sizeof(info),
				.fMask = MIIM_STATE,
				.fState = static_cast<UINT>(value ? MFS_CHECKED : MFS_UNCHECKED)
			};
			winrt::check_bool(PopupMenu::setMenuItemInfo(m_parentMenu, index, &info));
			if (value && !GroupName().empty())
			{
				assert(m_groupHelper);
				m_groupHelper->SetCheckedItem(*this);
			}
		}
	}
	winrt::hstring RadioPopupMenuFlyoutItem::GroupName()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(GroupNameProperty()));
	}
	void RadioPopupMenuFlyoutItem::GroupName(winrt::hstring const& value)
	{
		SetValue(GroupNameProperty(), winrt::box_value(value));
		if (!value.empty() && IsChecked())
			m_groupHelper->SetCheckedItem(*this);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty RadioPopupMenuFlyoutItem::IsCheckedProperty()
	{
		return s_isCheckedProperty;
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty RadioPopupMenuFlyoutItem::GroupNameProperty()
	{
		return s_groupNameProperty;
	}
	void RadioPopupMenuFlyoutItem::SetGroupHelper(RadioPopupMenuItemGroup& groupHelper)
	{
		m_groupHelper = &groupHelper;
	}
}
