#pragma once

#include "NavigationViewItemHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct NavigationViewItemHelper : NavigationViewItemHelperT<NavigationViewItemHelper>
    {
		static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
		static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem const& navigationViewItem);
		static void SetAcrylicWorkaround(
			winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem const& navigationViewItem,
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
    struct NavigationViewItemHelper : NavigationViewItemHelperT<NavigationViewItemHelper, implementation::NavigationViewItemHelper>
    {
    };
}
