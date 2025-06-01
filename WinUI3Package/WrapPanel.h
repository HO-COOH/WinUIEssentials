#pragma once

#include "WrapPanel.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct WrapPanel : WrapPanelT<WrapPanel>
    {
        WrapPanel() = default;

        double HorizontalSpacing();
        void HorizontalSpacing(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty HorizontalSpacingProperty();

        double VerticalSpacing();
        void VerticalSpacing(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty VerticalSpacingProperty();

        winrt::Microsoft::UI::Xaml::Controls::Orientation Orientation();
        void Orientation(winrt::Microsoft::UI::Xaml::Controls::Orientation value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty OrientationProperty();

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_horizontalSpacingProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_verticalSpacingProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_orientationProperty;

        static void propertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WrapPanel : WrapPanelT<WrapPanel, implementation::WrapPanel>
    {
    };
}
