#pragma once

#include "LineGraphControl.g.h"

namespace winrt::WinUI3Example::implementation
{
    template<typename T, T InitialMin, T InitialMax>
    class Axis
    {
        double  m_min = DBL_MAX;
        double  m_max = DBL_MIN;

    public:
        double Range() const
        {
            assert(m_max >= m_min);
            return m_max - m_min;
        }

        double Scale() const
        {

        }

        double AddPoint(double value)
        {
            m_min = min(m_min, value);
            m_max = max(m_max, value);
            return (value - m_min) / Range();
        }
    };
    struct LineGraphControl : LineGraphControlT<LineGraphControl>
    {
        LineGraphControl()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void AddPoint(double x, double y);

    private:
        Axis<double, 0.0, 1.0> axis_x;
        Axis<double, 0.0, 1.0> axis_y;
        int m_count;
        double m_points[2];

        double getX(double x);
    public:
        void Shape_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void Shape_PointerExited(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
        void Shape_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct LineGraphControl : LineGraphControlT<LineGraphControl, implementation::LineGraphControl>
    {
    };
}
