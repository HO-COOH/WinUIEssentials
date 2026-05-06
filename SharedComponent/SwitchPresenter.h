#pragma once

#include "SwitchPresenter.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct SwitchPresenter : SwitchPresenterT<SwitchPresenter>, EnsureDependencyProperty<SwitchPresenter>
    {
        static void EnsureDependencyProperties();
        SwitchPresenter();

        PackageRoot::Case CurrentCase();
        void CurrentCase(PackageRoot::Case const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty CurrentCaseProperty();

        PackageRoot::CaseCollection SwitchCases();
        void SwitchCases(PackageRoot::CaseCollection const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty SwitchCasesProperty();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_currentCaseProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_switchCasesProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_valueProperty = nullptr;

        static void onSwitchCasesChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void onValueChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void evaluateCases();
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SwitchPresenter : SwitchPresenterT<SwitchPresenter, implementation::SwitchPresenter>
    {
    };
}
