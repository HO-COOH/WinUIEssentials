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

        constexpr static int DoubleToInt32(double value) noexcept
        {
            return static_cast<int>(value);
        }

        static winrt::hstring DoubleToString(double value);
        static winrt::hstring DoubleToString(double value, int32_t precision);
        static bool ContainerToBool(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& container);
        static bool ReferenceToBool(winrt::Windows::Foundation::IInspectable const& value);
        static bool StringToBool(winrt::hstring const& value);
        constexpr static bool VisibilityToBool(Microsoft::UI::Xaml::Visibility value) noexcept
        {
            return value == winrt::Microsoft::UI::Xaml::Visibility::Visible;
        }

        static bool ContainerToBoolReverse(winrt::Windows::Foundation::Collections::IVector<Windows::Foundation::IInspectable> const& container);
        static bool ReferenceToBoolReverse(winrt::Windows::Foundation::IInspectable const& value);
        static bool StringToBoolReverse(winrt::hstring const& value);
        constexpr static bool VisibilityToBoolReverse(winrt::Microsoft::UI::Xaml::Visibility value) noexcept
        {
            return !VisibilityToBool(value);
        }

        static winrt::Microsoft::UI::Xaml::Visibility ContainerToVisibility(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& container);
        static winrt::Microsoft::UI::Xaml::Visibility ReferenceToVisibility(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::Visibility StringToVisibility(winrt::hstring const& value);
        constexpr static winrt::Microsoft::UI::Xaml::Visibility BoolToVisibility(bool value) noexcept
        {
            return value ? winrt::Microsoft::UI::Xaml::Visibility::Visible : winrt::Microsoft::UI::Xaml::Visibility::Collapsed;
        }

        static winrt::Microsoft::UI::Xaml::Visibility ContainerToVisibilityReverse(winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> const& container);
        static winrt::Microsoft::UI::Xaml::Visibility ReferenceToVisibilityReverse(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::Visibility StringToVisibilityReverse(winrt::hstring const& value);
        constexpr static Microsoft::UI::Xaml::Visibility BoolToVisibilityReverse(bool value) noexcept
        {
            return value ? winrt::Microsoft::UI::Xaml::Visibility::Collapsed : winrt::Microsoft::UI::Xaml::Visibility::Visible;
        }

        constexpr static bool ReverseBool(bool value) noexcept
        {
            return !value;
        }
        constexpr static winrt::Microsoft::UI::Xaml::Visibility ReverseVisibility(winrt::Microsoft::UI::Xaml::Visibility value) noexcept
        {
            return value == winrt::Microsoft::UI::Xaml::Visibility::Visible ? winrt::Microsoft::UI::Xaml::Visibility::Collapsed : winrt::Microsoft::UI::Xaml::Visibility::Visible;
        }
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Convert : ConvertT<Convert, implementation::Convert>
    {
    };
}
