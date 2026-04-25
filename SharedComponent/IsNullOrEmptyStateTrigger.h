#pragma once

#include "IsNullOrEmptyStateTrigger.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger>, EnsureDependencyProperty<IsNullOrEmptyStateTrigger>
    {
        static void EnsureDependencyProperties();
        IsNullOrEmptyStateTrigger();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_valueProperty = nullptr;
        static void onValuePropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const e);

        void updateTrigger();
        static bool isNullOrEmpty(winrt::Windows::Foundation::IInspectable val);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct IsNullOrEmptyStateTrigger : IsNullOrEmptyStateTriggerT<IsNullOrEmptyStateTrigger, implementation::IsNullOrEmptyStateTrigger>
    {
    };
}
