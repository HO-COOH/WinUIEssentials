#pragma once

#include "ModalWindow.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ModalWindow : ModalWindowT<ModalWindow>
    {
		ModalWindow() = default;
		ModalWindow(winrt::Microsoft::UI::Xaml::Window const& parent);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ModalWindow : ModalWindowT<ModalWindow, implementation::ModalWindow>
    {
    };
}
