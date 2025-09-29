#pragma once

#include "DefaultAcrylicWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultAcrylicWindow : DefaultAcrylicWindowT<DefaultAcrylicWindow>
    {
        DefaultAcrylicWindow() = default;

        static winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind ToAcrylicKind(winrt::Windows::Foundation::IInspectable const& selection);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultAcrylicWindow : DefaultAcrylicWindowT<DefaultAcrylicWindow, implementation::DefaultAcrylicWindow>
    {
    };
}
