#pragma once

#include "SegmentedMarginConverter.g.h"

namespace winrt::UWPPackage::implementation
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

        winrt::Windows::UI::Xaml::Thickness LeftItemMargin();
        void LeftItemMargin(winrt::Windows::UI::Xaml::Thickness value);

        winrt::Windows::UI::Xaml::Thickness RightItemMargin();
        void RightItemMargin(winrt::Windows::UI::Xaml::Thickness value);

        winrt::Windows::UI::Xaml::Thickness MiddleItemMargin();
        void MiddleItemMargin(winrt::Windows::UI::Xaml::Thickness value);
    private:
        winrt::Windows::UI::Xaml::Thickness m_leftItemMargin{};
        winrt::Windows::UI::Xaml::Thickness m_rightItemMargin{};
        winrt::Windows::UI::Xaml::Thickness m_middleItemMargin{};
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SegmentedMarginConverter : SegmentedMarginConverterT<SegmentedMarginConverter, implementation::SegmentedMarginConverter>
    {
    };
}
