#pragma once

#include "CursorController.g.h"

namespace winrt::PackageRoot::implementation
{
    struct CursorController : CursorControllerT<CursorController>
    {
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty TypeProperty();
        static void SetType(winrt::WinUINamespace::UI::Xaml::UIElement obj, winrt::Windows::UI::Core::CoreCursorType type);
        static winrt::Windows::UI::Core::CoreCursorType GetType(winrt::WinUINamespace::UI::Xaml::UIElement obj);

    private:
        static void CursorChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject obj, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs e);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct CursorController : CursorControllerT<CursorController, implementation::CursorController>
    {
    };
}
