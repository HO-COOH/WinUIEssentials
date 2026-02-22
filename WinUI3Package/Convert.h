#pragma once

#include "Convert.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct Convert : ConvertT<Convert>
    {
        constexpr static float DoubleToSingle(double value) noexcept
        {
            return static_cast<float>(value);
        }

        static bool ContainerToBool(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container);
        static bool ReferenceToBool(Windows::Foundation::IInspectable const& value);
        static bool StringToBool(hstring const& value);
        constexpr static bool VisibilityToBool(Microsoft::UI::Xaml::Visibility value) noexcept
        {
            return value == Microsoft::UI::Xaml::Visibility::Visible;
        }

        static bool ContainerToBoolReverse(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container);
        static bool ReferenceToBoolReverse(Windows::Foundation::IInspectable const& value);
        static bool StringToBoolReverse(hstring const& value);
        constexpr static bool VisibilityToBoolReverse(Microsoft::UI::Xaml::Visibility value) noexcept
        {
            return !VisibilityToBool(value);
        }

        static Microsoft::UI::Xaml::Visibility ContainerToVisibility(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container);
        static Microsoft::UI::Xaml::Visibility ReferenceToVisibility(Windows::Foundation::IInspectable const& value);
        static Microsoft::UI::Xaml::Visibility StringToVisibility(hstring const& value);
        constexpr static Microsoft::UI::Xaml::Visibility BoolToVisibility(bool value) noexcept
        {
            return value ? Microsoft::UI::Xaml::Visibility::Visible : Microsoft::UI::Xaml::Visibility::Collapsed;
        }

        static Microsoft::UI::Xaml::Visibility ContainerToVisibilityReverse(Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container);
        static Microsoft::UI::Xaml::Visibility ReferenceToVisibilityReverse(Windows::Foundation::IInspectable const& value);
        static Microsoft::UI::Xaml::Visibility StringToVisibilityReverse(hstring const& value);
        constexpr static Microsoft::UI::Xaml::Visibility BoolToVisibilityReverse(bool value) noexcept
        {
            return value ? Microsoft::UI::Xaml::Visibility::Collapsed : Microsoft::UI::Xaml::Visibility::Visible;
        }

        constexpr static bool ReverseBool(bool value) noexcept
        {
            return !value;
        }
        constexpr static Microsoft::UI::Xaml::Visibility ReverseVisibility(Microsoft::UI::Xaml::Visibility value) noexcept
        {
            return value == Microsoft::UI::Xaml::Visibility::Visible ? Microsoft::UI::Xaml::Visibility::Collapsed : Microsoft::UI::Xaml::Visibility::Visible;
        }
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Convert : ConvertT<Convert, implementation::Convert>
    {
    };
}
