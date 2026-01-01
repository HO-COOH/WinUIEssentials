#pragma once

#include "WindowBackgroundHelper.g.h"
#include "SystemBackdropType.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowBackgroundHelper : WindowBackgroundHelperT<WindowBackgroundHelper>
    {
        WindowBackgroundHelper();

        winrt::Microsoft::UI::Xaml::Window Window();
        void Window(winrt::Microsoft::UI::Xaml::Window const& value);

        void SystemBackdrop(SystemBackdropType type);
    private:
        SystemBackdropType m_type;
        winrt::Microsoft::UI::Xaml::Window m_window{ nullptr };
        void setBackground(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush const& brush);
        void setBackgroundWithType();
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WindowBackgroundHelper : WindowBackgroundHelperT<WindowBackgroundHelper, implementation::WindowBackgroundHelper>
    {
    };
}
