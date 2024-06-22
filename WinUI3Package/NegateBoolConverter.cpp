#include "pch.h"
#include "NegateBoolConverter.h"
#if __has_include("NegateBoolConverter.g.cpp")
#include "NegateBoolConverter.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Windows::Foundation::IInspectable NegateBoolConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value,
        [[maybe_unused]] winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        winrt::Windows::Foundation::IInspectable const& parameter,
        [[maybe_unused]] winrt::hstring const& language)
    {
        return winrt::box_value(
            !winrt::unbox_value<bool>(value)
        );
    }

    winrt::Windows::Foundation::IInspectable NegateBoolConverter::ConvertBack(
        [[maybe_unused]] winrt::Windows::Foundation::IInspectable const& value,
        [[maybe_unused]] winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        [[maybe_unused]] winrt::Windows::Foundation::IInspectable const& parameter,
        [[maybe_unused]] winrt::hstring const& language)
    {
        throw std::exception{ "Not implemented" };
    }
}
