#include "pch.h"
#include "DependentValue.h"
#if __has_include("DependentValue.g.cpp")
#include "DependentValue.g.cpp"
#endif

namespace winrt::UWPPackage::implementation
{
    winrt::Windows::UI::Xaml::DependencyProperty DependentValue::m_valueProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"Value",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<winrt::UWPPackage::DependentValue>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{ winrt::box_value(0.0),
            [](winrt::Windows::UI::Xaml::DependencyObject obj, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs args)
            {
                obj.as<winrt::UWPPackage::DependentValue>().Value(winrt::unbox_value<double>(args.NewValue()));
            } }
    );

    winrt::Windows::UI::Xaml::DependencyProperty DependentValue::ValueProperty()
    {
        return m_valueProperty;
    }

    double DependentValue::Value()
    {
        return winrt::unbox_value<double>(GetValue(m_valueProperty));
    }
    void DependentValue::Value(double value)
    {
        SetValue(m_valueProperty, winrt::box_value(value));
        m_valueChanged(*this, value);
    }
    winrt::event_token DependentValue::ValueChanged(winrt::Windows::Foundation::EventHandler<double> const& handler)
    {
        return m_valueChanged.add(handler);
    }
    void DependentValue::ValueChanged(winrt::event_token const& token)
    {
        m_valueChanged.remove(token);
    }
}
