﻿#pragma once

#include "DependentValue.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct DependentValue : DependentValueT<DependentValue>
    {
        DependentValue() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();

        double Value();
        void Value(double value);

        winrt::event_token ValueChanged(winrt::Windows::Foundation::EventHandler<double> const& handler);
        void ValueChanged(winrt::event_token const& token);
    private:
        winrt::event<winrt::Windows::Foundation::EventHandler<double>> m_valueChanged;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_valueProperty;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct DependentValue : DependentValueT<DependentValue, implementation::DependentValue>
    {
    };
}
