#pragma once

#include "IsEqualStringTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct IsEqualStringTrigger : IsEqualStringTriggerT<IsEqualStringTrigger>, EnsureDependencyProperty<IsEqualStringTrigger>
    {
        static void EnsureDependencyProperties();
        IsEqualStringTrigger() = default;

        winrt::hstring From();
        void From(winrt::hstring value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty FromProperty();

        winrt::hstring To();
        void To(winrt::hstring value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ToProperty();

    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty m_fromProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty m_toProperty = nullptr;

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
