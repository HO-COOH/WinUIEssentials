#pragma once

#include "ReferenceToVisibilityConverter.g.h"
#include "ReverseConverterBase.hpp"

namespace winrt::PackageRoot::implementation
{
    struct ReferenceToVisibilityConverter : ReferenceToVisibilityConverterT<ReferenceToVisibilityConverter>, ReverseConverterBase
    {
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

namespace winrt::PackageRoot::factory_implementation
{
    struct ReferenceToVisibilityConverter : ReferenceToVisibilityConverterT<ReferenceToVisibilityConverter, implementation::ReferenceToVisibilityConverter>
    {
    };
}
