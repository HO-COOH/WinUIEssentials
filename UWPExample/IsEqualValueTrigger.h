#pragma once

#include "IsEqualValueTrigger.g.h"

namespace winrt::UWPExample::implementation
{
    struct IsEqualValueTrigger : IsEqualValueTriggerT<IsEqualValueTrigger>
    {
        IsEqualValueTrigger() = default;

        winrt::Windows::Foundation::IInspectable From();
        void From(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty FromProperty();

        winrt::Windows::Foundation::IInspectable To();
        void To(winrt::Windows::Foundation::IInspectable value);
        static winrt::Windows::UI::Xaml::DependencyProperty ToProperty();

    private:
        static winrt::Windows::UI::Xaml::DependencyProperty m_fromProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_toProperty;

        static void onValuePropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct IsEqualValueTrigger : IsEqualValueTriggerT<IsEqualValueTrigger, implementation::IsEqualValueTrigger>
    {
    };
}
