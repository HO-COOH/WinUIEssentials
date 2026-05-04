#pragma once

#include "SegmentedItemCornerRadiusConverter.g.h"

namespace winrt::PackageRoot::implementation
{
    struct SegmentedItemCornerRadiusConverter : SegmentedItemCornerRadiusConverterT<SegmentedItemCornerRadiusConverter>
    {
        SegmentedItemCornerRadiusConverter() = default;

        winrt::WinUINamespace::UI::Xaml::CornerRadius SegmentedCornerRadius();
        void SegmentedCornerRadius(winrt::WinUINamespace::UI::Xaml::CornerRadius value);

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

        static bool isHorizontalLayout(winrt::WinUINamespace::UI::Xaml::Controls::Panel const& panel);
        winrt::WinUINamespace::UI::Xaml::CornerRadius m_cornerRadius{};
        bool m_set{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct SegmentedItemCornerRadiusConverter : SegmentedItemCornerRadiusConverterT<SegmentedItemCornerRadiusConverter, implementation::SegmentedItemCornerRadiusConverter>
    {
    };
}
