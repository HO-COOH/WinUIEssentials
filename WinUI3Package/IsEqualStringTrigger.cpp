#include "pch.h"
#include "IsEqualStringTrigger.h"
#if __has_include("IsEqualStringTrigger.g.cpp")
#include "IsEqualStringTrigger.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStringTrigger::m_fromProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<WinUI3Package::IsEqualStringTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualStringTrigger::onValuePropertyChanged }
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStringTrigger::m_toProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"To",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<WinUI3Package::IsEqualStringTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualStringTrigger::onValuePropertyChanged }
	);




	winrt::hstring IsEqualStringTrigger::From()
	{
		return winrt::unbox_value_or(GetValue(m_fromProperty), L"");
	}

	void IsEqualStringTrigger::From(winrt::hstring value)
	{
		SetValue(m_fromProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStringTrigger::FromProperty()
	{
		return m_fromProperty;
	}

	winrt::hstring IsEqualStringTrigger::To()
	{
		return winrt::unbox_value_or(GetValue(m_toProperty), L"");
	}

	void IsEqualStringTrigger::To(winrt::hstring value)
	{
		SetValue(m_toProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStringTrigger::ToProperty()
	{
		return m_toProperty;
	}

	void IsEqualStringTrigger::onValuePropertyChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<IsEqualStringTrigger>(d.as<WinUI3Package::IsEqualStringTrigger>())->updateTrigger();
	}

	void IsEqualStringTrigger::updateTrigger()
	{
		SetActive(From() == To());
	}
}
