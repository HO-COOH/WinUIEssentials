#pragma once

#include "IsEqualStringTrigger.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct IsEqualStringTrigger : IsEqualStringTriggerT<IsEqualStringTrigger>
    {
        IsEqualStringTrigger() = default;

        winrt::hstring From();
        void From(winrt::hstring value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty FromProperty();

        winrt::hstring To();
        void To(winrt::hstring value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ToProperty();

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_fromProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_toProperty;

        static void onValuePropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct IsEqualStringTrigger : IsEqualStringTriggerT<IsEqualStringTrigger, implementation::IsEqualStringTrigger>
    {
    };
}
