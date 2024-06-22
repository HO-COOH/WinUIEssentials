#pragma once

#include "IsEqualStateTrigger.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger>
    {
        IsEqualStateTrigger() = default;

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();

        winrt::Windows::Foundation::IInspectable To();
        void To(winrt::Windows::Foundation::IInspectable value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ToProperty();

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_valueProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_toProperty;

        static void onValuePropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
        static bool convertTypeEquals(
            winrt::Windows::Foundation::IInspectable value1,
            winrt::Windows::Foundation::IInspectable value2
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger, implementation::IsEqualStateTrigger>
    {
    };
}
