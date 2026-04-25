#pragma once

#include "WrapPanel.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct WrapPanel : WrapPanelT<WrapPanel>, EnsureDependencyProperty<WrapPanel>
    {
        static void EnsureDependencyProperties();
        WrapPanel() = default;

        double HorizontalSpacing();
        void HorizontalSpacing(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HorizontalSpacingProperty();

        double VerticalSpacing();
        void VerticalSpacing(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty VerticalSpacingProperty();

        winrt::WinUINamespace::UI::Xaml::Controls::Orientation Orientation();
        void Orientation(winrt::WinUINamespace::UI::Xaml::Controls::Orientation value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty OrientationProperty();

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_horizontalSpacingProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_verticalSpacingProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_orientationProperty = nullptr;

        static void propertyChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
			winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct WrapPanel : WrapPanelT<WrapPanel, implementation::WrapPanel>
    {
    };
}
