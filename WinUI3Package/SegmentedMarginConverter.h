#pragma once

#include "SegmentedMarginConverter.g.h"

namespace winrt::WinUI3Package::implementation
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

        winrt::Microsoft::UI::Xaml::Thickness LeftItemMargin();
        void LeftItemMargin(winrt::Microsoft::UI::Xaml::Thickness value);

        winrt::Microsoft::UI::Xaml::Thickness RightItemMargin();
        void RightItemMargin(winrt::Microsoft::UI::Xaml::Thickness value);

        winrt::Microsoft::UI::Xaml::Thickness MiddleItemMargin();
        void MiddleItemMargin(winrt::Microsoft::UI::Xaml::Thickness value);
    private:
        winrt::Microsoft::UI::Xaml::Thickness m_leftItemMargin{};
        winrt::Microsoft::UI::Xaml::Thickness m_rightItemMargin{};
        winrt::Microsoft::UI::Xaml::Thickness m_middleItemMargin{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct SegmentedMarginConverter : SegmentedMarginConverterT<SegmentedMarginConverter, implementation::SegmentedMarginConverter>
    {
    };
}
