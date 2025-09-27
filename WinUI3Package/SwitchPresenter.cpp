#include "pch.h"
#include "SwitchPresenter.h"
#if __has_include("SwitchPresenter.g.cpp")
#include "SwitchPresenter.g.cpp"
#endif
#include "CaseCollection.h"
#include "ObjectCompare.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty SwitchPresenter::s_currentCaseProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CurrentCase",
			winrt::xaml_typename<WinUI3Package::Case>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty SwitchPresenter::s_switchCasesProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"SwitchCases",
			winrt::xaml_typename<WinUI3Package::CaseCollection>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &SwitchPresenter::onSwitchCasesChanged }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty SwitchPresenter::s_valueProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &SwitchPresenter::onValueChanged }
		);

	SwitchPresenter::SwitchPresenter()
	{
		SwitchCases({});
		Loaded([this](auto&&...)
		{
			evaluateCases();
			SwitchCases().VectorChanged([this](auto&&...) { evaluateCases(); });
		});
	}

	WinUI3Package::Case SwitchPresenter::CurrentCase()
	{
		return GetValue(CurrentCaseProperty()).try_as<WinUI3Package::Case>();
	}

	void SwitchPresenter::CurrentCase(WinUI3Package::Case const& value)
	{
		SetValue(CurrentCaseProperty(), value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty SwitchPresenter::CurrentCaseProperty()
	{
		return s_currentCaseProperty;
	}

	WinUI3Package::CaseCollection SwitchPresenter::SwitchCases()
	{
		return GetValue(SwitchCasesProperty()).as<WinUI3Package::CaseCollection>();
	}

	void SwitchPresenter::SwitchCases(WinUI3Package::CaseCollection const& value)
	{
		SetValue(SwitchCasesProperty(), value);
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty SwitchPresenter::SwitchCasesProperty()
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

	winrt::Microsoft::UI::Xaml::DependencyProperty SwitchPresenter::ValueProperty()
	{
		return s_valueProperty;
	}

	void SwitchPresenter::onSwitchCasesChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{
		winrt::get_self<SwitchPresenter>(d.as<WinUI3Package::SwitchPresenter>())->evaluateCases();
	}

	void SwitchPresenter::onValueChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<SwitchPresenter>(d.as<WinUI3Package::SwitchPresenter>())->evaluateCases();
	}

	void SwitchPresenter::evaluateCases()
	{
		auto value = Value();
		if (!value)
			return;

		// If the current case we're on already matches our current value,
		// then we don't have any work to do.
		if (auto const& currentCase = CurrentCase(); currentCase)
		{
			// currentCase might be a default case, not having a value
			auto currentCaseValue = currentCase.Value();
			if (currentCaseValue && internal::ConvertTypeEquals(currentCaseValue, value))
				return;
		}

		auto cases = SwitchCases();
		if (cases.Size() == 0 )
			return;

		if (auto const& matchCase = winrt::get_self<implementation::CaseCollection>(cases)->EvaluateCases(value);
			matchCase != CurrentCase())
		{
			//match case can be null
			if (matchCase)
				Content(matchCase.Content());
			CurrentCase(matchCase);
		}
	}
}
