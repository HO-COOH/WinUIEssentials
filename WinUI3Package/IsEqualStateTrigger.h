#pragma once

#include "IsEqualStateTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger>, EnsureDependencyProperty<IsEqualStateTrigger>
    {
        static void EnsureDependencyProperties();
        IsEqualStateTrigger() = default;

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();

        winrt::Windows::Foundation::IInspectable To();
        void To(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ToProperty();

    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty m_valueProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty m_toProperty = nullptr;

        static void onValuePropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger, implementation::IsEqualStateTrigger>
    {
    };
}
