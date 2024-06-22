#include "pch.h"
#include "ContainerToBoolConverter.h"
#if __has_include("ContainerToBoolConverter.g.cpp")
#include "ContainerToBoolConverter.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
    winrt::Windows::Foundation::IInspectable ContainerToBoolConverter::Convert(
        winrt::Windows::Foundation::IInspectable const& value,
        [[maybe_unused]] winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        winrt::Windows::Foundation::IInspectable const& parameter,
        [[maybe_unused]] winrt::hstring const& language)
    {
        auto boolValue = false;
        if (value)
        {
            auto container = reinterpret_cast<winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable>*>(
                const_cast<winrt::Windows::Foundation::IInspectable*>(&value)
                );
            boolValue = container->Size();
        }

        if (Reverse() || (parameter && winrt::unbox_value<winrt::hstring>(parameter) == L"Reverse"))
            boolValue = !boolValue;

        return winrt::box_value(boolValue);
    }

    winrt::Windows::Foundation::IInspectable ContainerToBoolConverter::ConvertBack(
        [[maybe_unused]] winrt::Windows::Foundation::IInspectable const& value,
        [[maybe_unused]] winrt::Windows::UI::Xaml::Interop::TypeName const& targetType,
        [[maybe_unused]] winrt::Windows::Foundation::IInspectable const& parameter,
        [[maybe_unused]] winrt::hstring const& language)
    {
        throw std::exception{ "Not implemented" };
    }
}
