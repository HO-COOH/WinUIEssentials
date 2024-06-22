#include "pch.h"
#include "ReferenceToBoolConverter.h"
#if __has_include("ReferenceToBoolConverter.g.cpp")
#include "ReferenceToBoolConverter.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Windows::Foundation::IInspectable ReferenceToBoolConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value,
        [[maybe_unused]] winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        winrt::Windows::Foundation::IInspectable const& parameter,
        [[maybe_unused]] winrt::hstring const& language)
    {
        auto boolValue = static_cast<bool>(value);
        if (Reverse() || (parameter && winrt::unbox_value<winrt::hstring>(parameter) == L"Reverse"))
            boolValue = !boolValue;

        return winrt::box_value(boolValue);
    }

    winrt::Windows::Foundation::IInspectable ReferenceToBoolConverter::ConvertBack(
        [[maybe_unused]] winrt::Windows::Foundation::IInspectable const& value,
        [[maybe_unused]] winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        [[maybe_unused]] winrt::Windows::Foundation::IInspectable const& parameter,
        [[maybe_unused]] winrt::hstring const& language)
    {
        throw std::exception{ "Not implemented" };
    }
}
