#pragma once

#include "HostBackdropVisual.g.h"
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Microsoft.UI.Content.h>
#include "EnsureSystemDispatcherQueueController.hpp"
#include "include/TemplateControlHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct HostBackdropVisual : HostBackdropVisualT<HostBackdropVisual>, EnsureSystemDispatcherQueueController<HostBackdropVisual>, TemplateControlHelper<HostBackdropVisual>
    {
        HostBackdropVisual();

        void OnApplyTemplate();

        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/HostBackdropVisual_Resource.xaml";

    private:
        winrt::Microsoft::UI::Xaml::FrameworkElement m_acrylicContainer{ nullptr };
        winrt::Microsoft::UI::Content::ContentExternalOutputLink m_externalLink{ nullptr };

        constexpr static auto AcrylicContainer = L"AcrylicContainer";

        void sizeChanged(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& args
        );

        void cornerRadiusChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& self,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& cornerRadiusProperty
        );

        void paddingChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& self,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& paddingProperty
        );

        void createPlacementVisual(
            winrt::Windows::UI::Composition::Visual const& rootVisual
        );

        winrt::Windows::UI::Composition::CompositionRoundedRectangleGeometry m_clipGeometry{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct HostBackdropVisual : HostBackdropVisualT<HostBackdropVisual, implementation::HostBackdropVisual>
    {
    };
}
