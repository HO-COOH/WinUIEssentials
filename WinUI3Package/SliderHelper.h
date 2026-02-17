#pragma once

#include "SliderHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct SliderHelper : SliderHelperT<SliderHelper>
    {
		SliderHelper() = default;

		static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
		static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::Slider const& slider);
		static void SetAcrylicWorkaround(
			winrt::Microsoft::UI::Xaml::Controls::Slider const& slider,
			bool value
		);

	private:
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

		static void applyThumbAcrylic(winrt::Microsoft::UI::Xaml::Controls::Primitives::Thumb const& thumb);

		static void acrylicWorkaroundChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& object,
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
		);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct SliderHelper : SliderHelperT<SliderHelper, implementation::SliderHelper>
    {
    };
}
