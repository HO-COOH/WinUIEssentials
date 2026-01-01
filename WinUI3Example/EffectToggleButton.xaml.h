#pragma once

#include "EffectToggleButton.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowBackgroundHelper;

    struct EffectToggleButton : EffectToggleButtonT<EffectToggleButton>
    {
        EffectToggleButton() = default;
        
        winrt::WinUI3Example::WindowBackgroundHelper Window();
        void Window(winrt::WinUI3Example::WindowBackgroundHelper const& value);

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        int m_effectIndex{};

        winrt::WinUI3Example::WindowBackgroundHelper m_window{ nullptr };
        WindowBackgroundHelper* m_windowImpl{};
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct EffectToggleButton : EffectToggleButtonT<EffectToggleButton, implementation::EffectToggleButton>
    {
    };
}
