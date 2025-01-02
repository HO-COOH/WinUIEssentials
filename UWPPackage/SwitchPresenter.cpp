#include "pch.h"
#include "SwitchPresenter.h"
#if __has_include("SwitchPresenter.g.cpp")
#include "SwitchPresenter.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::s_currentCaseProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"CurrentCase",
			winrt::xaml_typename<UWPPackage::Case>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::s_switchCasesProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"SwitchCases",
			winrt::xaml_typename<UWPPackage::CaseCollection>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::s_valueProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	UWPPackage::Case SwitchPresenter::CurrentCase()
	{
		return GetValue(CurrentCaseProperty()).as<UWPPackage::Case>();
	}

	void SwitchPresenter::CurrentCase(UWPPackage::Case const& value)
	{
		SetValue(CurrentCaseProperty(), value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::CurrentCaseProperty()
	{
		return s_currentCaseProperty;
	}

	UWPPackage::CaseCollection SwitchPresenter::SwitchCases()
	{
		return GetValue(SwitchCasesProperty()).as<UWPPackage::CaseCollection>();
	}

	void SwitchPresenter::SwitchCases(UWPPackage::CaseCollection const& value)
	{
		SetValue(SwitchCasesProperty(), value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::SwitchCasesProperty()
	{
		return s_switchCasesProperty;
	}

	winrt::Windows::Foundation::IInspectable SwitchPresenter::Value()
	{
		return GetValue(ValueProperty());
	}

	void SwitchPresenter::Value(winrt::Windows::Foundation::IInspectable const& value)
	{
		SetValue(ValueProperty(), value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::ValueProperty()
	{
		return s_valueProperty;
	}

	void SwitchPresenter::onSwitchCasesChanged(
		winrt::Windows::UI::Xaml::DependencyObject const& d,
		winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{

	}
}
