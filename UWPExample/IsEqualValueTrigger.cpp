#include "pch.h"
#include "IsEqualValueTrigger.h"
#if __has_include("IsEqualValueTrigger.g.cpp")
#include "IsEqualValueTrigger.g.cpp"
#endif

namespace winrt::UWPExample::implementation
{
	winrt::Windows::UI::Xaml::DependencyProperty IsEqualValueTrigger::m_fromProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<UWPExample::IsEqualValueTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualValueTrigger::onValuePropertyChanged }
	);

	winrt::Windows::UI::Xaml::DependencyProperty IsEqualValueTrigger::m_toProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"To",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<UWPExample::IsEqualValueTrigger>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualValueTrigger::onValuePropertyChanged }
	);




	winrt::Windows::Foundation::IInspectable IsEqualValueTrigger::From()
	{
		return GetValue(m_fromProperty);
	}

	void IsEqualValueTrigger::From(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_fromProperty, value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty IsEqualValueTrigger::FromProperty()
	{
		return m_fromProperty;
	}

	winrt::Windows::Foundation::IInspectable IsEqualValueTrigger::To()
	{
		return GetValue(m_toProperty);
	}

	void IsEqualValueTrigger::To(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_toProperty, value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty IsEqualValueTrigger::ToProperty()
	{
		return m_toProperty;
	}

	void IsEqualValueTrigger::onValuePropertyChanged(
		winrt::Windows::UI::Xaml::DependencyObject d,
		winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<IsEqualValueTrigger>(d.as<UWPExample::IsEqualValueTrigger>())->updateTrigger();
	}

	void IsEqualValueTrigger::updateTrigger()
	{
		SetActive(From() == To());
	}
}
