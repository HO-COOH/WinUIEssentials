#pragma once

#include "ColorPickerHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ColorPickerHelper
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& colorPicker);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& colorPicker,
            bool value
        );

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

		static void applyAcrylic(winrt::Microsoft::UI::Xaml::Controls::Primitives::ColorSpectrum const& colorSpectrum);
        static void applyAcrylic(winrt::Microsoft::UI::Xaml::Controls::Slider const& slider);
		static void applyAcrylicToOwnedToolTip(winrt::Microsoft::UI::Xaml::DependencyObject const& tooltipOwner);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ColorPickerHelper : ColorPickerHelperT<ColorPickerHelper, implementation::ColorPickerHelper>
    {
    };
}
