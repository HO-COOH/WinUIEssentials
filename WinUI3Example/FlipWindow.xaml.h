#pragma once

#include "FlipWindow.g.h"
#include <winrt/Microsoft.UI.Windowing.h>
#include <HwndHelper.hpp>

template<typename T>
T ScaleForDpi(auto value, UINT dpi)
{
    return value * dpi / 96.0;
}

namespace winrt::WinUI3Example::implementation
{
    struct FlipWindow : FlipWindowT<FlipWindow>
    {
        FlipWindow();

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void RootGrid_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        constexpr static double GetCanvasLeftOffset(double controlWidth, double canvasWidth)
        {
            return (canvasWidth - controlWidth) / 2.0;
        }

        double ContentWidth();
        double ContentHeight();

        double WindowWidth();
        double WindowHeight();
    private:
        constexpr static auto c_WindowWidth = 1280;
        constexpr static auto c_WindowHeight = 720;
        constexpr static auto ShadowRadius = 20.f;

        void createCompositionObjects();
        winrt::Microsoft::UI::Composition::Visual m_frontVisual{ nullptr };
        winrt::Microsoft::UI::Composition::Visual m_backVisual{ nullptr };
        winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation m_frontVisualRotationAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation m_backVisualRotationAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ExpressionAnimation m_frontVisualOpacityAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ExpressionAnimation m_backVisualOpacityAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ExpressionAnimation m_centerPointAnimation{ nullptr };
        winrt::Microsoft::UI::Composition::ContainerVisual m_shadowVisual{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FlipWindow : FlipWindowT<FlipWindow, implementation::FlipWindow>
    {
    };
}
