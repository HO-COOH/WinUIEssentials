#pragma once

#include "DependentValue.g.h"
#include "../include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct DependentValue : DependentValueT<DependentValue>, EnsureDependencyProperty<DependentValue>
    {
        static void EnsureDependencyProperties();
        DependentValue() = default;

        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();

        double Value();
        void Value(double value);

        winrt::event_token ValueChanged(winrt::Windows::Foundation::EventHandler<double> const& handler);
        void ValueChanged(winrt::event_token const& token);
    private:
        winrt::event<winrt::Windows::Foundation::EventHandler<double>> m_valueChanged;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty m_valueProperty = nullptr;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct DependentValue : DependentValueT<DependentValue, implementation::DependentValue>
    {
    };
}
