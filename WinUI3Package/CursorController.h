#pragma once

#include "CursorController.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct CursorController : CursorControllerT<CursorController>
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty TypeProperty();
        static void SetType(winrt::Microsoft::UI::Xaml::UIElement obj, winrt::Windows::UI::Core::CoreCursorType type);
        static winrt::Windows::UI::Core::CoreCursorType GetType(winrt::Microsoft::UI::Xaml::UIElement obj);

    private:
        static void CursorChanged(winrt::Microsoft::UI::Xaml::DependencyObject obj, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs e);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CursorController : CursorControllerT<CursorController, implementation::CursorController>
    {
    };
}
