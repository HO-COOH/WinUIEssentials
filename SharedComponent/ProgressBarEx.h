#pragma once

#include "ProgressBarEx.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include <include/TemplateControlHelper.hpp>

namespace winrt::PackageRoot::implementation
{
    struct ProgressBarEx : ProgressBarExT<ProgressBarEx>, TemplateControlHelper<ProgressBarEx>, EnsureDependencyProperty<ProgressBarEx>
    {
        static void EnsureDependencyProperties();
        ProgressBarEx() = default;

        void OnApplyTemplate();

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/ProgressBarEx_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/ProgressBarEx_Resource.xaml";
#endif

        winrt::Windows::UI::Color HighColor();
        void HighColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HighColorProperty();

        winrt::Windows::UI::Color BaseColor();
        void BaseColor(winrt::Windows::UI::Color value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty BaseColorProperty();


        double Percent();
        void Percent(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty PercentProperty();

        double Value();
        void Value(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();
    private:
        static void onPercentPropertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        winrt::WinUINamespace::UI::Composition::Compositor m_compositor{ nullptr };
        winrt::WinUINamespace::UI::Composition::CompositionColorGradientStop m_gradients[4]{ nullptr, nullptr, nullptr, nullptr };
        winrt::WinUINamespace::UI::Composition::SpriteVisual m_spriteVisual{ nullptr };
        //winrt::WinUINamespace::UI::Composition::Vector2KeyFrameAnimation m_valueAnimation{ nullptr };

        void setSpriteSize();
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_highColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_baseColorProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_percentProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_valueProperty = nullptr;

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

namespace winrt::PackageRoot::factory_implementation
{
    struct ProgressBarEx : ProgressBarExT<ProgressBarEx, implementation::ProgressBarEx>
    {
    };
}
