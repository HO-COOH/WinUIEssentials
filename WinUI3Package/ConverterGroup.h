#pragma once

#include "ConverterGroup.g.h"

namespace winrt::WinUI3Package::implementation
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

        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Data::IValueConverter> Converters();
        void Converters(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Data::IValueConverter> value);
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Data::IValueConverter> m_converters =
            winrt::single_threaded_vector<winrt::Microsoft::UI::Xaml::Data::IValueConverter>();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ConverterGroup : ConverterGroupT<ConverterGroup, implementation::ConverterGroup>
    {
    };
}
