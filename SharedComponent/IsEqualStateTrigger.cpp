#include "pch.h"
#include "IsEqualStateTrigger.h"
#if __has_include("IsEqualStateTrigger.g.cpp")
#include "IsEqualStateTrigger.g.cpp"
#endif
#include "ObjectCompare.h"

namespace winrt::PackageRoot::implementation
{
	void IsEqualStateTrigger::EnsureDependencyProperties()
	{
		if (m_valueProperty) return;
		m_valueProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::IsEqualStateTrigger>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &IsEqualStateTrigger::onValuePropertyChanged }
		);
		m_toProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"To",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<PackageRoot::IsEqualStateTrigger>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &IsEqualStateTrigger::onValuePropertyChanged }
		);
	}

	winrt::Windows::Foundation::IInspectable IsEqualStateTrigger::Value()
	{
		return GetValue(m_valueProperty);
	}

	void IsEqualStateTrigger::Value(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_valueProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty IsEqualStateTrigger::ValueProperty()
	{
		return m_valueProperty;
	}

	winrt::Windows::Foundation::IInspectable IsEqualStateTrigger::To()
	{
		return GetValue(m_toProperty);
	}

	void IsEqualStateTrigger::To(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_toProperty, value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty IsEqualStateTrigger::ToProperty()
	{
		return m_toProperty;
	}

	void IsEqualStateTrigger::onValuePropertyChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<IsEqualStateTrigger>(d.as<PackageRoot::IsEqualStateTrigger>())->updateTrigger();
	}

	void IsEqualStateTrigger::updateTrigger()
	{
		bool isActive = false;

		auto value = Value();
		auto to = To();

		if (value && to)
		{
			isActive = internal::ConvertTypeEquals(value, to);
		}
		else if (!value && !to)
		{
			isActive = true;
		}

		SetActive(isActive);
	}

}
