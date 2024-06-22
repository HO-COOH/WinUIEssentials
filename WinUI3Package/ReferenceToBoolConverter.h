#pragma once

#include "ReferenceToBoolConverter.g.h"
#include "ReverseConverterBase.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct ReferenceToBoolConverter : ReferenceToBoolConverterT<ReferenceToBoolConverter>, ReverseConverterBase
    {
        ReferenceToBoolConverter() = default;

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

namespace winrt::WinUI3Package::factory_implementation
{
    struct ReferenceToBoolConverter : ReferenceToBoolConverterT<ReferenceToBoolConverter, implementation::ReferenceToBoolConverter>
    {
    };
}
