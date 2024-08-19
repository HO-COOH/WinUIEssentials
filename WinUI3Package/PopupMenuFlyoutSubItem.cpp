#include "pch.h"
#include "PopupMenuFlyoutSubItem.h"
#if __has_include("PopupMenuFlyoutSubItem.g.cpp")
#include "PopupMenuFlyoutSubItem.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutSubItem::s_iconProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Icon",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::IconElement>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutSubItem::s_textProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Text",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::Controls::IconElement PopupMenuFlyoutSubItem::Icon()
	{
		return GetValue(IconProperty()).as<winrt::Microsoft::UI::Xaml::Controls::IconElement>();
	}
	void PopupMenuFlyoutSubItem::Icon(winrt::Microsoft::UI::Xaml::Controls::IconElement const& value)
	{
		SetValue(IconProperty(), value);
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutSubItem::IconProperty()
	{
		return s_iconProperty;
	}
	winrt::hstring PopupMenuFlyoutSubItem::Text()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(TextProperty()));
	}
	void PopupMenuFlyoutSubItem::Text(winrt::hstring const& value)
	{
		SetValue(TextProperty(), winrt::box_value(value));
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutSubItem::TextProperty()
	{
		return s_textProperty;
	}
}
