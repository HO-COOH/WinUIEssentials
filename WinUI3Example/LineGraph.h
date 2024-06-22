#pragma once

#include "LineGraph.g.h"
#include <winrt/Microsoft.UI.Composition.h>

namespace winrt::WinUI3Example::implementation
{
    struct LineGraph : LineGraphT<LineGraph>
    {
        LineGraph() = default;

        void AddPoint(double x, double y);
    private:
        winrt::Microsoft::UI::Xaml::Controls::Grid m_rootGrid{ nullptr };
        winrt::Microsoft::UI::Composition::Compositor m_compositor;
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct LineGraph : LineGraphT<LineGraph, implementation::LineGraph>
    {
    };
}
