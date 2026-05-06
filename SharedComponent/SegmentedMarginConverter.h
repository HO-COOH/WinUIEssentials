#pragma once

#include "SegmentedMarginConverter.g.h"

namespace winrt::PackageRoot::implementation
{
    struct SegmentedMarginConverter : SegmentedMarginConverterT<SegmentedMarginConverter>
    {
        SegmentedMarginConverter() = default;

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

        winrt::WinUINamespace::UI::Xaml::Thickness LeftItemMargin();
        void LeftItemMargin(winrt::WinUINamespace::UI::Xaml::Thickness value);

        winrt::WinUINamespace::UI::Xaml::Thickness RightItemMargin();
        void RightItemMargin(winrt::WinUINamespace::UI::Xaml::Thickness value);

        winrt::WinUINamespace::UI::Xaml::Thickness MiddleItemMargin();
        void MiddleItemMargin(winrt::WinUINamespace::UI::Xaml::Thickness value);
    private:
        winrt::WinUINamespace::UI::Xaml::Thickness m_leftItemMargin{};
        winrt::WinUINamespace::UI::Xaml::Thickness m_rightItemMargin{};
        winrt::WinUINamespace::UI::Xaml::Thickness m_middleItemMargin{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SegmentedMarginConverter : SegmentedMarginConverterT<SegmentedMarginConverter, implementation::SegmentedMarginConverter>
    {
    };
}
