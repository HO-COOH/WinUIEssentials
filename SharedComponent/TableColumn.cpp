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

	void TableColumn::onStringContentChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d, 
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{

	}
}
