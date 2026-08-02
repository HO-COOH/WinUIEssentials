#pragma once

#include "Case.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::PackageRoot::implementation
{
    struct Case : CaseT<Case>, EnsureDependencyProperty<Case>
    {
        static void EnsureDependencyProperties();

        winrt::Windows::Foundation::IInspectable Content();
        void Content(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ContentProperty();

        bool IsDefault();
        void IsDefault(bool value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty IsDefaultProperty();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_contentProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_isDefaultProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_valueProperty;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct Case : CaseT<Case, implementation::Case>
    {
    };
}
