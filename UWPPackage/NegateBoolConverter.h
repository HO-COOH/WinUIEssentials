#pragma once

#include "NegateBoolConverter.g.h"

namespace winrt::UWPPackage::implementation
{
    struct NegateBoolConverter : NegateBoolConverterT<NegateBoolConverter>
    {
        NegateBoolConverter() = default;

        winrt::Windows::Foundation::IInspectable Convert(
            winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
            winrt::Windows::Foundation::IInspectable const& parameter,
            winrt::hstring const& language
        );

        winrt::Windows::Foundation::IInspectable ConvertBack(
            winrt::Windows::Foundation::IInspectable const& value,
            winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
            winrt::Windows::Foundation::IInspectable const& parameter,
            winrt::hstring const& language
        );
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct NegateBoolConverter : NegateBoolConverterT<NegateBoolConverter, implementation::NegateBoolConverter>
    {
    };
}
