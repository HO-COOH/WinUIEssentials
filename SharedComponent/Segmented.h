#pragma once

#include "Segmented.g.h"
#include "include/TemplateControlHelper.hpp"
#include "ListViewBaseWorkaround.hpp"

namespace winrt::PackageRoot::implementation
{
    struct Segmented : ListViewBaseWorkaround<SegmentedT<Segmented>>, TemplateControlHelper<Segmented>
    {
        Segmented();

        void OnApplyTemplate();

#if defined Build_WinUIPackage
        constexpr static auto ResourceUri = L"ms-appx:///WinUI3Package/Segmented_Resource.xaml";
#else
        constexpr static auto ResourceUri = L"ms-appx:///UWPPackage/Segmented_Resource.xaml";
#endif

        winrt::Windows::Foundation::Numerics::float2 SelectedItemActualWidth();
        winrt::Windows::Foundation::Numerics::float2 SelectedItemOffset();
    private:
        void onSelectedIndexChanged(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::WinUINamespace::UI::Xaml::Controls::SelectionChangedEventArgs const& arg
        );
        void onSelectionModeChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& sender,
            winrt::WinUINamespace::UI::Xaml::DependencyProperty const& indexProperty
        );
        void onHorizontalAlignmentChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& sender,
            winrt::WinUINamespace::UI::Xaml::DependencyProperty const& horizontalAlignmentProperty
        );
        void onItemsPanelChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& sender,
            winrt::WinUINamespace::UI::Xaml::DependencyProperty const& itemsPanelProperty
        );

        void setMultiSelectStyle(bool value);

        winrt::WinUINamespace::UI::Xaml::Controls::Border m_knob{ nullptr };

        winrt::WinUINamespace::UI::Xaml::Media::Animation::DoubleAnimation m_knobTranslateXAnimation{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Media::Animation::DoubleAnimation m_knobTranslateYAnimation{ nullptr };

        winrt::WinUINamespace::UI::Xaml::Media::Animation::DoubleAnimation m_knobWidthAnimation{ nullptr };
        winrt::WinUINamespace::UI::Xaml::Media::Animation::DoubleAnimation m_knobHeightAnimation{ nullptr };

        winrt::WinUINamespace::UI::Xaml::Media::Animation::Storyboard m_knobAnimation{ nullptr };
        winrt::WinUINamespace::UI::Xaml::FrameworkElement::SizeChanged_revoker m_knobSizeChangeRevoker;

        bool m_isFirst = true;
        bool m_isMultiSelect = false;
        int m_internalSelectedIndex = -1;
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct Segmented : SegmentedT<Segmented, implementation::Segmented>
    {
    };
}
