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

        constexpr static double GetCanvasLeftOffset(double controlWidth, double canvasWidth)
        {
            return (canvasWidth - controlWidth) / 2.0;
        }

        double ContentWidth();
        double ContentHeight();

        double WindowWidth();
        double WindowHeight();
        
        constexpr double AnimationDuration()
        {
            return m_animationDurationMilli;
        }

        void AnimationDuration(double value);

    private:
        constexpr static auto c_WindowWidth = 1280;
        constexpr static auto c_WindowHeight = 720;
        constexpr static auto ShadowRadius = 20.f;
        double m_animationDurationMilli = 1000;
        void createCompositionObjects();
        void addShadows();
        winrt::Microsoft::UI::Composition::Visual m_frontVisual{ nullptr };
        winrt::Microsoft::UI::Composition::Visual m_backVisual{ nullptr };
        winrt::Microsoft::UI::Composition::SpriteVisual m_frontShadow{ nullptr };
        winrt::Microsoft::UI::Composition::SpriteVisual m_backShadow{ nullptr };
        winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation rotationAnimation{ nullptr };
        winrt::Windows::Foundation::Numerics::float3 m_rotationAxis{ 0.f, 1.f, 0.f };
    public:
        void GoBackButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void RadioButtons_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FlipWindow : FlipWindowT<FlipWindow, implementation::FlipWindow>
    {
    };
}
