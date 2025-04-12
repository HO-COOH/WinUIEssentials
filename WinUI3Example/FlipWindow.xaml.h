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

        static double GetCanvasLeftOffset(double controlWidth, double canvasWidth)
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

        winrt::Microsoft::UI::Composition::ContainerVisual shadowVisual{ nullptr };
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct FlipWindow : FlipWindowT<FlipWindow, implementation::FlipWindow>
    {
    };
}
