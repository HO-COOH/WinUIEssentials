#pragma once

#include "Case.g.h"

namespace winrt::UWPPackage::implementation
{
    struct Case : CaseT<Case>
    {
        Case() = default;

        winrt::Windows::Foundation::IInspectable Content();
        void Content(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Windows::UI::Xaml::DependencyProperty ContentProperty();

        bool IsDefault();
        void IsDefault(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsDefaultProperty();

        winrt::Windows::Foundation::IInspectable Value();
        void Value(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Windows::UI::Xaml::DependencyProperty ValueProperty();
        
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_contentProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_isDefaultProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_valueProperty;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct Case : CaseT<Case, implementation::Case>
    {
    };
}
