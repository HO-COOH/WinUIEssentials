#pragma once

#include "WindowWithCustomMenu.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowWithCustomMenu : WindowWithCustomMenuT<WindowWithCustomMenu>
    {
        void myButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WindowWithCustomMenu : WindowWithCustomMenuT<WindowWithCustomMenu, implementation::WindowWithCustomMenu>
    {
    };
}
