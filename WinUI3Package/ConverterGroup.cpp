#include "pch.h"
#include "ConverterGroup.h"
#if __has_include("ConverterGroup.g.cpp")
#include "ConverterGroup.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Windows::Foundation::IInspectable ConverterGroup::Convert(
        winrt::Windows::Foundation::IInspectable const& value,
        winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        winrt::Windows::Foundation::IInspectable const& parameter,
        winrt::hstring const& language)
    {
        auto copy = value;
        for (auto converter : m_converters)
        {
            copy = converter.Convert(copy, targetType, parameter, language);
        }
        return copy;
    }

    winrt::Windows::Foundation::IInspectable ConverterGroup::ConvertBack(
        winrt::Windows::Foundation::IInspectable const& value,
        winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        winrt::Windows::Foundation::IInspectable const& parameter,
        winrt::hstring const& language)
    {
        throw std::exception{ "Not implemented" };
    }

    winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Data::IValueConverter> ConverterGroup::Converters()
    {
        return m_converters;
    }

    void ConverterGroup::Converters(winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::UI::Xaml::Data::IValueConverter> value)
    {
        m_converters = value;
    }
}
