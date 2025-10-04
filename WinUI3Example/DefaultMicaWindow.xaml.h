#pragma once

#include "DefaultMicaWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct DefaultMicaWindow : DefaultMicaWindowT<DefaultMicaWindow>
    {
        DefaultMicaWindow() = default;

        static winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind ToMicaKind(winrt::Windows::Foundation::IInspectable const& selection);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct DefaultMicaWindow : DefaultMicaWindowT<DefaultMicaWindow, implementation::DefaultMicaWindow>
    {
    };
}
