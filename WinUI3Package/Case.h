#pragma once

#include "Case.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct Case : CaseT<Case>
    {
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
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_contentProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_isDefaultProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_valueProperty;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Case : CaseT<Case, implementation::Case>
    {
    };
}
