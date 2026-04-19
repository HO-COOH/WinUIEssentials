#pragma once

#include "IsNullOrEmptyStateTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger>, EnsureDependencyProperty<IsNullOrEmptyStateTrigger>
    {
        static void EnsureDependencyProperties();
        IsNullOrEmptyStateTrigger();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty m_valueProperty = nullptr;
        static void onValuePropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const e);

        void updateTrigger();
        static bool isNullOrEmpty(winrt::Windows::Foundation::IInspectable val);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger, implementation::IsNullOrEmptyStateTrigger>
    {
    };
}
