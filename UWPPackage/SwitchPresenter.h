#pragma once

#include "SwitchPresenter.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SwitchPresenter : SwitchPresenterT<SwitchPresenter>
    {
        SwitchPresenter() = default;

        UWPPackage::Case CurrentCase();
        void CurrentCase(UWPPackage::Case const& value);
        static winrt::Windows::UI::Xaml::DependencyProperty CurrentCaseProperty();

        UWPPackage::CaseCollection SwitchCases();
        void SwitchCases(UWPPackage::CaseCollection const& value);
        static winrt::Windows::UI::Xaml::DependencyProperty SwitchCasesProperty();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Windows::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_currentCaseProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_switchCasesProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_valueProperty;

        static void onSwitchCasesChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SwitchPresenter : SwitchPresenterT<SwitchPresenter, implementation::SwitchPresenter>
    {
    };
}
