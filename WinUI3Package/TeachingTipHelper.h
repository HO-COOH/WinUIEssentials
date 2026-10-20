#pragma once

#include "TeachingTipHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct TeachingTipHelper
    {
		static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
		static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip);
		static void SetAcrylicWorkaround(
			winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
			bool value
		);

	private:
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

		static void acrylicWorkaroundChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& object,
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
		);

		//container is the root of the TeachingTip's ControlTemplate, where the template elements are found by name
		static void applyForNonTargeted(
			winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
			winrt::Microsoft::UI::Xaml::FrameworkElement const& container
		);
		static void applyForTargeted(
			winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
			winrt::Microsoft::UI::Xaml::FrameworkElement const& container
		);
		static void applyBody(
			winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
			winrt::Microsoft::UI::Xaml::FrameworkElement const& container,
			winrt::Microsoft::UI::Xaml::Controls::Grid const& contentRootGrid
		);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TeachingTipHelper : TeachingTipHelperT<TeachingTipHelper, implementation::TeachingTipHelper>
    {
    };
}
