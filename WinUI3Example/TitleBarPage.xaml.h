#pragma once

#include "TitleBarPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct TitleBarPage : TitleBarPageT<TitleBarPage>
    {
        TitleBarPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        void CreateWin32Window_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void CreateCustomWindow_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TitleBarPage : TitleBarPageT<TitleBarPage, implementation::TitleBarPage>
    {
    };
}
