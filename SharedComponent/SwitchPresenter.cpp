#include "pch.h"
#include "SwitchPresenter.h"
#if __has_include("SwitchPresenter.g.cpp")
#include "SwitchPresenter.g.cpp"
#endif
#include "CaseCollection.h"
#include "ObjectCompare.h"

namespace winrt::PackageRoot::implementation
{
	void SwitchPresenter::EnsureDependencyProperties()
	{
		if (s_currentCaseProperty) return;
		s_currentCaseProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"CurrentCase",
			winrt::xaml_typename<PackageRoot::Case>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);
		s_switchCasesProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"SwitchCases",
			winrt::xaml_typename<PackageRoot::CaseCollection>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &SwitchPresenter::onSwitchCasesChanged }
		);
		s_valueProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
			L"Value",
			winrt::xaml_typename<winrt::Windows::Foundation::IInspectable>(),
			winrt::xaml_typename<class_type>(),
			winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &SwitchPresenter::onValueChanged }
		);
	}

	SwitchPresenter::SwitchPresenter()
	{
		SwitchCases({});
		Loaded([this](auto&&...)
		{
			evaluateCases();
			SwitchCases().VectorChanged([this](auto&&...) { evaluateCases(); });
		});
	}

	PackageRoot::Case SwitchPresenter::CurrentCase()
	{
		return GetValue(CurrentCaseProperty()).try_as<PackageRoot::Case>();
	}

	void SwitchPresenter::CurrentCase(PackageRoot::Case const& value)
	{
		SetValue(CurrentCaseProperty(), value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty SwitchPresenter::CurrentCaseProperty()
	{
		return s_currentCaseProperty;
	}

	PackageRoot::CaseCollection SwitchPresenter::SwitchCases()
	{
		return GetValue(SwitchCasesProperty()).as<PackageRoot::CaseCollection>();
	}

	void SwitchPresenter::SwitchCases(PackageRoot::CaseCollection const& value)
	{
		SetValue(SwitchCasesProperty(), value);
	}

	winrt::WinUINamespace::UI::Xaml::DependencyProperty SwitchPresenter::SwitchCasesProperty()
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

	winrt::WinUINamespace::UI::Xaml::DependencyProperty SwitchPresenter::ValueProperty()
	{
		return s_valueProperty;
	}

	void SwitchPresenter::onSwitchCasesChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{
		winrt::get_self<SwitchPresenter>(d.as<PackageRoot::SwitchPresenter>())->evaluateCases();
	}

	void SwitchPresenter::onValueChanged(
		winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
		winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		winrt::get_self<SwitchPresenter>(d.as<PackageRoot::SwitchPresenter>())->evaluateCases();
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
