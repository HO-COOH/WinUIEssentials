#pragma once

#include "ProgressBarEx.g.h"
#include <include/TemplateControlHelper.hpp>
#include <winrt/Windows.UI.Composition.h>

namespace winrt::UWPPackage::implementation
{
    struct ProgressBarEx : ProgressBarExT<ProgressBarEx>, TemplateControlHelper<ProgressBarEx>
    {
        ProgressBarEx() = default;

        void OnApplyTemplate();

        winrt::Windows::UI::Color HighColor();
        void HighColor(winrt::Windows::UI::Color value);
        static winrt::Windows::UI::Xaml::DependencyProperty HighColorProperty();

        winrt::Windows::UI::Color BaseColor();
        void BaseColor(winrt::Windows::UI::Color value);
        static winrt::Windows::UI::Xaml::DependencyProperty BaseColorProperty();


        double Percent();
        void Percent(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty PercentProperty();

        double Value();
        void Value(double value);
        static winrt::Windows::UI::Xaml::DependencyProperty ValueProperty();
    private:
        static void onPercentPropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        winrt::Windows::UI::Composition::Compositor m_compositor{ nullptr };
        winrt::Windows::UI::Composition::CompositionColorGradientStop m_gradients[4]{ nullptr, nullptr, nullptr, nullptr };
        winrt::Windows::UI::Composition::SpriteVisual m_spriteVisual{ nullptr };

        void setSpriteSize();
        static winrt::Windows::UI::Xaml::DependencyProperty s_highColorProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_baseColorProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_percentProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_valueProperty;

        static constexpr winrt::Windows::UI::Color DefaultHighColor{ 255, 0, 255, 0 };
        static constexpr winrt::Windows::UI::Color DefaultBaseColor{ 100, 0, 255, 0 };
        static constexpr float gradientStop[]
        {
            0.273f,
            0.436f,
            0.482f,
            0.643f,
        };
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct ProgressBarEx : ProgressBarExT<ProgressBarEx, implementation::ProgressBarEx>
    {
    };
}
