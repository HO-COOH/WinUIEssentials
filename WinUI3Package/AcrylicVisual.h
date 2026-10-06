#pragma once

#include "AcrylicVisual.g.h"
#include <winrt/Microsoft.UI.Content.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include "PlacementVisualBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct AcrylicVisual : AcrylicVisualT<AcrylicVisual>, PlacementVisualBase
    {
        AcrylicVisual();

        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
    private:
        winrt::Microsoft::UI::Content::ContentExternalBackdropLink m_backdropLink{ nullptr };
        winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController m_controller{ nullptr };

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
