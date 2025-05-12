#pragma once

#include "AcrylicVisual.g.h"
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

namespace winrt::WinUI3Package::implementation
{
    struct AcrylicVisual : AcrylicVisualT<AcrylicVisual>
    {
        AcrylicVisual();

        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);

        winrt::Windows::Foundation::Numerics::float4 ClipOffset{};
        winrt::Microsoft::UI::Composition::Visual m_placementVisual{ nullptr };
    private:
        void cornerRadiusChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& self,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& cornerRadiusProperty
        );

        void paddingChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& self,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& paddingProperty
        );

        winrt::Microsoft::UI::Content::ContentExternalBackdropLink m_backdropLink{ nullptr };
        winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController m_controller{ nullptr };

        winrt::Microsoft::UI::Composition::RectangleClip m_clip{ nullptr };
        static winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configuration;
        void updateVisual();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct AcrylicVisual : AcrylicVisualT<AcrylicVisual, implementation::AcrylicVisual>
    {
    };
}
