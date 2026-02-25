#pragma once

#include "SampleModalWindow.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SampleModalWindow : SampleModalWindowT<SampleModalWindow>
    {
        SampleModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent);
        void ModalWindow_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SampleModalWindow : SampleModalWindowT<SampleModalWindow, implementation::SampleModalWindow>
    {
    };
}
