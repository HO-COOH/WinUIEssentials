﻿#pragma once

#include "ProgressBarEx.g.h"
#include <include/TemplateControlHelper.hpp>
#include <winrt/Microsoft.UI.Composition.h>

namespace winrt::WinUI3Package::implementation
{
    struct ProgressBarEx : ProgressBarExT<ProgressBarEx>, TemplateControlHelper<ProgressBarEx>
    {
        ProgressBarEx() = default;

        void OnApplyTemplate();

        winrt::Windows::UI::Color HighColor();
        void HighColor(winrt::Windows::UI::Color value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty HighColorProperty();

        winrt::Windows::UI::Color BaseColor();
        void BaseColor(winrt::Windows::UI::Color value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty BaseColorProperty();


        double Percent();
        void Percent(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty PercentProperty();

        double Value();
        void Value(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();
    private:
        static void onPercentPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        winrt::Microsoft::UI::Composition::Compositor m_compositor{ nullptr };
        winrt::Microsoft::UI::Composition::CompositionColorGradientStop m_gradients[4]{ nullptr, nullptr, nullptr, nullptr };
        winrt::Microsoft::UI::Composition::SpriteVisual m_spriteVisual{ nullptr };
        //winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_valueAnimation{ nullptr };

        void setSpriteSize();
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_highColorProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_baseColorProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_percentProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_valueProperty;

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

namespace winrt::WinUI3Package::factory_implementation
{
    struct ProgressBarEx : ProgressBarExT<ProgressBarEx, implementation::ProgressBarEx>
    {
    };
}
