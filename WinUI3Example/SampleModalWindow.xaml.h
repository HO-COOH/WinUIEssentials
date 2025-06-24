#pragma once

#include "SampleModalWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SampleModalWindow : SampleModalWindowT<SampleModalWindow>
    {
        SampleModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SampleModalWindow : SampleModalWindowT<SampleModalWindow, implementation::SampleModalWindow>
    {
    };
}
