#pragma once

#include "ConverterGroup.g.h"

namespace winrt::UWPPackage::implementation
{
    struct ConverterGroup : ConverterGroupT<ConverterGroup>
    {
        ConverterGroup() = default;

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

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Data::IValueConverter> Converters();
        void Converters(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Data::IValueConverter> value);
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Data::IValueConverter> m_converters =
            winrt::single_threaded_vector<winrt::Windows::UI::Xaml::Data::IValueConverter>();
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct ConverterGroup : ConverterGroupT<ConverterGroup, implementation::ConverterGroup>
    {
    };
}
