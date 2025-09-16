#pragma once

#include "ElementThemeToStringConverter.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct ElementThemeToStringConverter : ElementThemeToStringConverterT<ElementThemeToStringConverter>
    {
        ElementThemeToStringConverter() = default;

		winrt::Windows::Foundation::IInspectable Convert(
            winrt::Windows::Foundation::IInspectable const& value, 
            winrt::Windows::UI::Xaml::Interop::TypeName const& targetType, 
            winrt::Windows::Foundation::IInspectable const& parameter, 
            winrt::hstring const& language);

		winrt::Windows::Foundation::IInspectable ConvertBack(
			winrt::Windows::Foundation::IInspectable const& value,
			winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
			winrt::Windows::Foundation::IInspectable const& parameter,
			winrt::hstring const& language);

    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct ElementThemeToStringConverter : ElementThemeToStringConverterT<ElementThemeToStringConverter, implementation::ElementThemeToStringConverter>
    {
    };
}
