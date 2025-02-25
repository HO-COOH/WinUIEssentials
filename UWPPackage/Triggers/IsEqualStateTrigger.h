#pragma once

#include "IsEqualStateTrigger.g.h"

namespace winrt::UWPPackage::implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger>
    {
        IsEqualStateTrigger() = default;

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ValueProperty();

        winrt::Windows::Foundation::IInspectable To();
        void To(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ToProperty();

    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_valueProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_toProperty;

        static void onValuePropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger, implementation::IsEqualStateTrigger>
    {
    };
}
