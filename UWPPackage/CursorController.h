#pragma once

#include "CursorController.g.h"

namespace winrt::UWPPackage::implementation
{
    struct CursorController : CursorControllerT<CursorController>
    {
        CursorController() = default;

        static winrt::Windows::UI::Xaml::DependencyProperty TypeProperty();
        static void SetType(winrt::Windows::UI::Xaml::UIElement obj, winrt::Windows::UI::Core::CoreCursorType type);
        static winrt::Windows::UI::Core::CoreCursorType GetType(winrt::Windows::UI::Xaml::UIElement obj);

    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_typeProperty;

        static void CursorChanged(winrt::Windows::UI::Xaml::DependencyObject obj, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs e);
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct CursorController : CursorControllerT<CursorController, implementation::CursorController>
    {
    };
}
