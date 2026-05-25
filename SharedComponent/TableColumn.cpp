#include "pch.h"
#include "TableColumn.h"
#if __has_include("TableColumn.g.cpp")
#include "TableColumn.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	void TableColumn::EnsureDependencyProperties()
	{
		if (s_stringContentProperty) return;

		s_stringContentProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"StringContent",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &TableColumn::onStringContentChanged }
		);
		s_itemTemplateProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"ItemTemplate",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::DataTemplate>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &TableColumn::onItemTemplateChanged }
		);
		s_editTemplateProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"EditTemplate",
			winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::DataTemplate>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &TableColumn::onEditTemplateChanged }
		);
		s_sortEnabledProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"SortEnabled",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(false), &TableColumn::onSortEnabledChanged }
		);
	}

	winrt::hstring TableColumn::StringContent()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(StringContentProperty()));
	}

	void TableColumn::StringContent(winrt::hstring const& value)
	{
		SetValue(StringContentProperty(), winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty TableColumn::StringContentProperty()
	{
		return s_stringContentProperty;
	}

	winrt::WinUINamespace::UI::Xaml::DataTemplate TableColumn::ItemTemplate()
	{
		return GetValue(s_itemTemplateProperty).as<winrt::WinUINamespace::UI::Xaml::DataTemplate>();
	}

	void TableColumn::ItemTemplate(winrt::WinUINamespace::UI::Xaml::DataTemplate const& value)
	{
		SetValue(s_itemTemplateProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty TableColumn::ItemTemplateProperty()
	{
		return s_itemTemplateProperty;
	}

	winrt::WinUINamespace::UI::Xaml::DataTemplate TableColumn::EditTemplate()
	{
		return GetValue(s_editTemplateProperty).as<winrt::WinUINamespace::UI::Xaml::DataTemplate>();
	}

	void TableColumn::EditTemplate(winrt::WinUINamespace::UI::Xaml::DataTemplate const& value)
	{
		SetValue(s_editTemplateProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty TableColumn::EditTemplateProperty()
	{
		return s_editTemplateProperty;
	}

	bool TableColumn::SortEnabled()
	{
		return winrt::unbox_value<bool>(GetValue(SortEnabledProperty()));
	}

	void TableColumn::SortEnabled(bool value)
	{
		SetValue(SortEnabledProperty(), winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty TableColumn::SortEnabledProperty()
	{
		return s_sortEnabledProperty;
	}

	void TableColumn::onStringContentChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<TableColumn>(d.as<class_type>())->m_data.m_stringContent = winrt::unbox_value<winrt::hstring>(e.NewValue());
	}

	void TableColumn::onItemTemplateChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<TableColumn>(d.as<class_type>())->m_data.m_itemTemplate = e.NewValue().as<winrt::WinUINamespace::UI::Xaml::DataTemplate>();
	}

	void TableColumn::onEditTemplateChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<TableColumn>(d.as<class_type>())->m_data.m_editTemplate = e.NewValue().as<winrt::WinUINamespace::UI::Xaml::DataTemplate>();
	}

	void TableColumn::onSortEnabledChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<TableColumn>(d.as<class_type>())->m_data.m_sortEnabled = winrt::unbox_value<bool>(e.NewValue());
	}
}
