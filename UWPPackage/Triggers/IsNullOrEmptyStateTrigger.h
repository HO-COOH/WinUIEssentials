#pragma once

#include "IsNullOrEmptyStateTrigger.g.h"

namespace winrt::UWPPackage::implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger>
    {
        IsNullOrEmptyStateTrigger();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_valueProperty;
        static void onValuePropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const e);

        void updateTrigger();
        static bool isNullOrEmpty(winrt::Windows::Foundation::IInspectable val);
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger, implementation::IsNullOrEmptyStateTrigger>
    {
    };
}
