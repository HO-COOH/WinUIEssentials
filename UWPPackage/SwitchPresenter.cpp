#include "pch.h"
#include "SwitchPresenter.h"
#if __has_include("SwitchPresenter.g.cpp")
#include "SwitchPresenter.g.cpp"
#endif
#include "ObjectCompare.h"
#include "CaseCollection.h"

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
			winrt::Windows::UI::Xaml::PropertyMetadata{nullptr, &SwitchPresenter::onSwitchCasesChanged}
		);

	winrt::Windows::UI::Xaml::DependencyProperty SwitchPresenter::s_valueProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{nullptr, &SwitchPresenter::onValueChanged}
		);

	SwitchPresenter::SwitchPresenter()
	{
		SwitchCases({});
	}

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
		winrt::get_self<SwitchPresenter>(d.as<UWPPackage::SwitchPresenter>())->evaluateCases();
	}

	void SwitchPresenter::onValueChanged(
		winrt::Windows::UI::Xaml::DependencyObject const& d, 
		winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<SwitchPresenter>(d.as<UWPPackage::SwitchPresenter>())->evaluateCases();
	}

	void SwitchPresenter::evaluateCases()
	{
		// If the current case we're on already matches our current value,
		// then we don't have any work to do.
		if (auto const& currentCase = CurrentCase(); currentCase)
		{
			// currentCase might be a default case, not having a value
			auto currentCaseValue = currentCase.Value();
			if(currentCaseValue && internal::ConvertTypeEquals(currentCaseValue, Value()))
				return;
		}

		auto cases = SwitchCases();
		if (cases.Size() == 0)
			return;
		if (auto const& matchCase = winrt::get_self<implementation::CaseCollection>(cases)->EvaluateCases(Value());
			matchCase != CurrentCase())
		{
			//match case can be null
			if (matchCase)
				Content(matchCase.Content());
			CurrentCase(matchCase);
		}
	}
}
