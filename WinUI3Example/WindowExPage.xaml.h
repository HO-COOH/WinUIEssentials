#pragma once

#include "WindowExPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct WindowExPage : WindowExPageT<WindowExPage>
    {
        WindowExPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct WindowExPage : WindowExPageT<WindowExPage, implementation::WindowExPage>
    {
    };
}
