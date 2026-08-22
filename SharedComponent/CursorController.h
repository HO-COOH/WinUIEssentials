#pragma once

#include "CursorController.g.h"

namespace winrt::PackageRoot::implementation
{
    struct CursorController
    {
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty TypeProperty();
        static void SetType(winrt::WinUINamespace::UI::Xaml::UIElement const& obj, winrt::Windows::UI::Core::CoreCursorType type);
        static winrt::Windows::UI::Core::CoreCursorType GetType(winrt::WinUINamespace::UI::Xaml::UIElement const& obj);

    private:
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_typeProperty;
        static void cursorChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& obj, 
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e);
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct CursorController : CursorControllerT<CursorController, implementation::CursorController>
    {
    };
}
