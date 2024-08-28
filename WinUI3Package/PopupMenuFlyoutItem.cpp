#include "pch.h"
#include "PopupMenuFlyoutItem.h"
#if __has_include("PopupMenuFlyoutItem.g.cpp")
#include "PopupMenuFlyoutItem.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Interop.h>
#include "PopupMenu.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::s_iconProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Icon",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::IconElement>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::s_textProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Text",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::s_commandProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Command",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Input::ICommand>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::s_commandParameterProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CommandParameter",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::s_visibilityProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Visibility",
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Visibility>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::WinUI3Package::PopupMenuFlyoutItemType PopupMenuFlyoutItem::Type()
	{
		return winrt::WinUI3Package::PopupMenuFlyoutItemType::MenuFlyoutItem;
	}

	winrt::Microsoft::UI::Xaml::Controls::IconElement PopupMenuFlyoutItem::Icon()
	{
		return GetValue(IconProperty()).as<winrt::Microsoft::UI::Xaml::Controls::IconElement>();
	}

	void PopupMenuFlyoutItem::Icon(winrt::Microsoft::UI::Xaml::Controls::IconElement const& value)
	{
		SetValue(IconProperty(), value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::IconProperty()
	{
		return s_iconProperty;
	}

	winrt::hstring PopupMenuFlyoutItem::Text()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(TextProperty()));
	}
	void PopupMenuFlyoutItem::Text(winrt::hstring const& value)
	{
		SetValue(TextProperty(), winrt::box_value(value));
		if (m_parent)
		{
			m_parent->onItemTextChanged(*this);
		}
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::TextProperty()
	{
		return s_textProperty;
	}

	winrt::Microsoft::UI::Xaml::Input::ICommand PopupMenuFlyoutItem::Command()
	{
		return GetValue(CommandProperty()).as<winrt::Microsoft::UI::Xaml::Input::ICommand>();
	}
	void PopupMenuFlyoutItem::Command(winrt::Microsoft::UI::Xaml::Input::ICommand const& value)
	{
		SetValue(CommandProperty(), value);
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::CommandProperty()
	{
		return s_commandProperty;
	}

	winrt::Windows::Foundation::IInspectable PopupMenuFlyoutItem::CommandParameter()
	{
		return GetValue(CommandParameterProperty());
	}

	void PopupMenuFlyoutItem::CommandParameter(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(CommandParameterProperty(), value);
	}
	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::CommandParameterProperty()
	{
		return s_commandParameterProperty;
	}

	winrt::Microsoft::UI::Xaml::Visibility PopupMenuFlyoutItem::Visibility()
	{
		return winrt::unbox_value<winrt::Microsoft::UI::Xaml::Visibility>(GetValue(VisibilityProperty()));
	}

	void PopupMenuFlyoutItem::Visibility(winrt::Microsoft::UI::Xaml::Visibility value)
	{
		SetValue(VisibilityProperty(), winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty PopupMenuFlyoutItem::VisibilityProperty()
	{
		return s_visibilityProperty;
	}

	winrt::event_token PopupMenuFlyoutItem::Click(winrt::Microsoft::UI::Xaml::RoutedEventHandler const& handler)
	{
		return m_clickEvent.add(handler);
	}

	void PopupMenuFlyoutItem::Click(winrt::event_token const& token)
	{
		m_clickEvent.remove(token);
	}

}
