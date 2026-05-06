#pragma once

#include "IsEqualStateTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger>, EnsureDependencyProperty<IsEqualStateTrigger>
    {
        static void EnsureDependencyProperties();
        IsEqualStateTrigger() = default;

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();

        winrt::Windows::Foundation::IInspectable To();
        void To(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ToProperty();

    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_valueProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_toProperty = nullptr;

        static void onValuePropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        void updateTrigger();
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct IsEqualStateTrigger : IsEqualStateTriggerT<IsEqualStateTrigger, implementation::IsEqualStateTrigger>
    {
    };
}
