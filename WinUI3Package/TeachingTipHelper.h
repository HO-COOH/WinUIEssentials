#pragma once

#include "TeachingTipHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct TeachingTipHelper : TeachingTipHelperT<TeachingTipHelper>
	{
		TeachingTipHelper() = default;

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
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TeachingTipHelper : TeachingTipHelperT<TeachingTipHelper, implementation::TeachingTipHelper>
    {
    };
}
