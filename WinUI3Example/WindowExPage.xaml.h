#pragma once

#include "WindowExPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowExPage : WindowExPageT<WindowExPage>
    {
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void CreateWin32Window_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateCustomWindow_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WindowExPage : WindowExPageT<WindowExPage, implementation::WindowExPage>
    {
    };
}
