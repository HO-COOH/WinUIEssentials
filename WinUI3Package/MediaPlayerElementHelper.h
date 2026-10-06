#pragma once

#include "MediaPlayerElementHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct MediaPlayerElementHelper
    {
		static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
		static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::MediaPlayerElement const& MediaPlayerElement);
		static void SetAcrylicWorkaround(
			winrt::Microsoft::UI::Xaml::Controls::MediaPlayerElement const& MediaPlayerElement,
			bool value
		);

	private:
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;
    
		static void acrylicWorkaroundChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d,
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
	};
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct MediaPlayerElementHelper : MediaPlayerElementHelperT<MediaPlayerElementHelper, implementation::MediaPlayerElementHelper>
    {
    };
}
