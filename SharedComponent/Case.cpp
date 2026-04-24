#include "pch.h"
#include "Case.h"
#if __has_include("Case.g.cpp")
#include "Case.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
	void Case::EnsureDependencyProperties()
	{
		if (s_contentProperty) return;
		s_contentProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Content",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		s_isDefaultProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"IsDefault",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		s_valueProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
	}

	winrt::Windows::Foundation::IInspectable Case::Content()
	{
		return GetValue(ContentProperty());
	}

	void Case::Content(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(ContentProperty(), value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty Case::ContentProperty()
	{
		return s_contentProperty;
	}

	bool Case::IsDefault()
	{
		return winrt::unbox_value<bool>(GetValue(IsDefaultProperty()));
	}

	void Case::IsDefault(bool value)
	{
		SetValue(IsDefaultProperty(), winrt::box_value(value));
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty Case::IsDefaultProperty()
	{
		return s_isDefaultProperty;
	}

	winrt::Windows::Foundation::IInspectable Case::Value()
	{
		return GetValue(ValueProperty());
	}

	void Case::Value(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(ValueProperty(), value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty Case::ValueProperty()
	{
		return s_valueProperty;
	}
}
