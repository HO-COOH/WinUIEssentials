#pragma once

#include "MediaTransportControlsHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct MediaTransportControlsHelper
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& MediaTransportControls);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& MediaTransportControls,
            bool value
        );

        static void ApplyAcrylicToMediaTransportControl(
            winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& mediaTransportControls
        );
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

        static void applyAcrylicToMediaTransportControlAfterLoaded(
            winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& mediaTransportControls
        );

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct MediaTransportControlsHelper : MediaTransportControlsHelperT<MediaTransportControlsHelper, implementation::MediaTransportControlsHelper>
    {
    };
}
