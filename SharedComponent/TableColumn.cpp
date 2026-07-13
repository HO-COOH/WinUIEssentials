#include "pch.h"
#include "TableColumn.h"
#if __has_include("TableColumn.g.cpp")
#include "TableColumn.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	void TableColumn::EnsureDependencyProperties()
	{
		if (s_contentProperty) return;

		s_contentProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Content",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
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
		s_isResizableProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"IsResizable",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ winrt::box_value(true), &TableColumn::onIsResizableChanged }
		);
	}

	winrt::Windows::Foundation::IInspectable TableColumn::Content()
	{
		return GetValue(s_contentProperty);
	}

	void TableColumn::Content(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(s_contentProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty TableColumn::ContentProperty()
	{
		return s_contentProperty;
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

	bool TableColumn::IsResizable()
	{
		return winrt::unbox_value<bool>(GetValue(s_isResizableProperty));
	}

	void TableColumn::IsResizable(bool value)
	{
		SetValue(s_isResizableProperty, winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty TableColumn::IsResizableProperty()
	{
		return s_isResizableProperty;
	}

	winrt::WinUINamespace::UI::Xaml::Controls::Flyout TableColumn::Flyout()
	{
		return m_flyout;
	}

	void TableColumn::Flyout(winrt::WinUINamespace::UI::Xaml::Controls::Flyout const& value)
	{
		m_flyout = value;
	}

	void TableColumn::onStringContentChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto& columnData = winrt::get_self<TableColumn>(d.as<class_type>())->m_data;
		auto newValue = e.NewValue();
		if (auto tryString = newValue.try_as<winrt::hstring>())
			columnData.m_content = std::move(*tryString);
		else
			columnData.m_content = newValue;
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

	void TableColumn::onIsResizableChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<TableColumn>(d.as<class_type>())->m_data.m_isResizable = winrt::unbox_value<bool>(e.NewValue());
	}
}
