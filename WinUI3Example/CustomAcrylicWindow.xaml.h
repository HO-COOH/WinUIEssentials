#pragma once

#include "CustomAcrylicWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct CustomAcrylicWindow : CustomAcrylicWindowT<CustomAcrylicWindow>
    {
        CustomAcrylicWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        static winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind ToAcrylicKind(winrt::Windows::Foundation::IInspectable const& selection);
        static float DoubleToSingle(double value);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct CustomAcrylicWindow : CustomAcrylicWindowT<CustomAcrylicWindow, implementation::CustomAcrylicWindow>
    {
    };
}
