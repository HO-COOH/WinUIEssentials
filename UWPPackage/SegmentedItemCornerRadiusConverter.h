#pragma once

#include "SegmentedItemCornerRadiusConverter.g.h"

namespace winrt::UWPPackage::implementation
{
    struct SegmentedItemCornerRadiusConverter : SegmentedItemCornerRadiusConverterT<SegmentedItemCornerRadiusConverter>
    {
        SegmentedItemCornerRadiusConverter() = default;

        winrt::Windows::UI::Xaml::CornerRadius SegmentedCornerRadius();
        void SegmentedCornerRadius(winrt::Windows::UI::Xaml::CornerRadius value);

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

    private:

        static bool isHorizontalLayout(winrt::Windows::UI::Xaml::Controls::Panel const& panel);
        winrt::Windows::UI::Xaml::CornerRadius m_cornerRadius{};
        bool m_set{};
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct SegmentedItemCornerRadiusConverter : SegmentedItemCornerRadiusConverterT<SegmentedItemCornerRadiusConverter, implementation::SegmentedItemCornerRadiusConverter>
    {
    };
}
