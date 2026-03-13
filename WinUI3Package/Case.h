#pragma once

#include "Case.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct Case : CaseT<Case>, EnsureDependencyProperty<Case>
    {
        static void EnsureDependencyProperties();
        Case() = default;

        winrt::Windows::Foundation::IInspectable Content();
        void Content(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ContentProperty();

        bool IsDefault();
        void IsDefault(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsDefaultProperty();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty ValueProperty();

    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_contentProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_isDefaultProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_valueProperty = nullptr;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Case : CaseT<Case, implementation::Case>
    {
    };
}
