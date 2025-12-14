#pragma once

#include "FlyoutHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
	struct FlyoutHelper : FlyoutHelperT<FlyoutHelper>
	{
		static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
		static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::Flyout const& flyout);
		static void SetAcrylicWorkaround(
			winrt::Microsoft::UI::Xaml::Controls::Flyout const& flyout,
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
    struct FlyoutHelper : FlyoutHelperT<FlyoutHelper, implementation::FlyoutHelper>
    {
    };
}
