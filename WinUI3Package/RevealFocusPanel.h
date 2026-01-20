#pragma once

#include "RevealFocusPanel.g.h"
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "RevealBrush.h"

namespace winrt::WinUI3Package::implementation
{
    struct RevealFocusPanel : RevealFocusPanelT<RevealFocusPanel>
    {
        RevealFocusPanel(winrt::Microsoft::UI::Xaml::FrameworkElement const& element);

		static winrt::Microsoft::UI::Xaml::DependencyProperty SetAsPanelProperty();
        static void SetSetAsPanel(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element, 
            bool value
		);
        static bool GetSetAsPanel(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element
		);

		static winrt::Microsoft::UI::Xaml::DependencyProperty AttachToPanelProperty();
		static void SetAttachToPanel(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element, 
            winrt::Microsoft::UI::Xaml::FrameworkElement const& panel
        );
        static winrt::Microsoft::UI::Xaml::FrameworkElement GetAttachToPanel(
            winrt::Microsoft::UI::Xaml::FrameworkElement const& element
        );
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_panelProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_setAsPanelProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_attachToPanelProperty;

        static void onSetAsPanelChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
        static void onAttachToPanelChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void createResourcesIfNeeded(
			winrt::Microsoft::UI::Xaml::FrameworkElement const& element
        );

        void onUpdateMousePosition(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& args
        );

        winrt::Microsoft::UI::Composition::Compositor m_compositor{ nullptr };
        winrt::Microsoft::UI::Composition::CompositionPropertySet m_globalPropertySet{ nullptr };
        winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation m_opacityForwardAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation m_opacityBackwardAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_revealBrushRadiusForwardAnimation{ nullptr };
		winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation m_revealBrushRadiusBackwardAnimation{ nullptr };

        //The same ExpressionAnimation can be used on multiple objects after you set its parameter
        winrt::Microsoft::UI::Composition::ExpressionAnimation m_hostVisualSizeExpressionAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ExpressionAnimation m_borderGeometrySizeExpressionAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ExpressionAnimation m_ellipseCenterExpressionAnimation{ nullptr };
		winrt::Microsoft::UI::Composition::ExpressionAnimation m_visualOffsetExpressionAnimation{ nullptr };

        constexpr static auto hostVisualSizeExpression = L"hostVisual.Size";
        constexpr static auto borderGeometrySizeExpression = L"hostVisual.Size - Vector2(strokeWidth, strokeWidth)";
        constexpr static auto ellipseCenterExpression = L"globalProperty.MousePosition - localProperty.elementPosition";
        constexpr static auto visualOffsetExpression = L"localProperty.elementPosition";

        constexpr static winrt::Windows::Foundation::Numerics::float2 InitialMousePosition{ (std::numeric_limits<float>::max)(), (std::numeric_limits<float>::max)() };

        // Container visual on the canvas that holds all overlay visuals
        winrt::Microsoft::UI::Composition::ContainerVisual m_overlayContainer{ nullptr };
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct RevealFocusPanel : RevealFocusPanelT<RevealFocusPanel, implementation::RevealFocusPanel>
    {
    };
}
