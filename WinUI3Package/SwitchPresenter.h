#pragma once

#include "SwitchPresenter.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct SwitchPresenter : SwitchPresenterT<SwitchPresenter>
    {
        SwitchPresenter();

        WinUI3Package::Case CurrentCase();
        void CurrentCase(WinUI3Package::Case const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty CurrentCaseProperty();

        WinUI3Package::CaseCollection SwitchCases();
        void SwitchCases(WinUI3Package::CaseCollection const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty SwitchCasesProperty();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_currentCaseProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_switchCasesProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_valueProperty;

        static void onSwitchCasesChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        static void onValueChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void evaluateCases();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct SwitchPresenter : SwitchPresenterT<SwitchPresenter, implementation::SwitchPresenter>
    {
    };
}
