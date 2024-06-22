#include "pch.h"
#include "IsEqualStateTrigger.h"
#if __has_include("IsEqualStateTrigger.g.cpp")
#include "IsEqualStateTrigger.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStateTrigger::m_valueProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<WinUI3Package::IsEqualStateTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualStateTrigger::onValuePropertyChanged }
	);

	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStateTrigger::m_toProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"To",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<WinUI3Package::IsEqualStateTrigger>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, &IsEqualStateTrigger::onValuePropertyChanged }
	);


	winrt::Windows::Foundation::IInspectable IsEqualStateTrigger::Value()
	{
		return GetValue(m_valueProperty);
	}

	void IsEqualStateTrigger::Value(winrt::Windows::Foundation::IInspectable value)
	{
		SetValue(m_valueProperty, value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStateTrigger::ValueProperty()
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

	winrt::Microsoft::UI::Xaml::DependencyProperty IsEqualStateTrigger::ToProperty()
	{
		return m_toProperty;
	}

	void IsEqualStateTrigger::onValuePropertyChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<IsEqualStateTrigger>(d.as<WinUI3Package::IsEqualStateTrigger>())->updateTrigger();
	}

	void IsEqualStateTrigger::updateTrigger()
	{
		bool isActive = false;

		auto value = Value();
		auto to = To();

		if (value && to)
		{
			isActive = convertTypeEquals(value, to);
		}
		else if (!value && !to)
		{
			isActive = true;
		}

		SetActive(isActive);
	}

	bool IsEqualStateTrigger::convertTypeEquals(
		winrt::Windows::Foundation::IInspectable object1,
		winrt::Windows::Foundation::IInspectable object2
	)
	{
		//try string
		{
			auto object1Converted = object1.try_as<winrt::hstring>();
			auto object2Converted = object2.try_as<winrt::hstring>();
			if (object1Converted && object2Converted)
				return object1Converted == object2Converted;
		}
		{
			auto object1Converted = winrt::unbox_value<ContentAlignment>(object1);
			auto object2Converted = object2.try_as<winrt::hstring>();
			switch (object1Converted)
			{
			case winrt::WinUI3Package::ContentAlignment::Right:
				return object2Converted == L"Right";
			case winrt::WinUI3Package::ContentAlignment::Left:
				return object2Converted == L"Left";
			case winrt::WinUI3Package::ContentAlignment::Vertical:
				return object2Converted == L"Vertical";
			default:
				false;
			}
		}
		//try object comparison
		{
			return object1 == object2;
		}
	}
}
