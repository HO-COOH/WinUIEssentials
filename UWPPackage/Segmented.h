#pragma once

#include "Segmented.g.h"
#include "include/TemplateControlHelper.hpp"


namespace winrt::UWPPackage::implementation
{
    struct Segmented : SegmentedT<Segmented>, TemplateControlHelper<Segmented>
    {
        Segmented();

        void OnApplyTemplate();

        winrt::Windows::Foundation::Numerics::float2 SelectedItemActualWidth();
        winrt::Windows::Foundation::Numerics::float2 SelectedItemOffset();
    private:
        void onSelectedIndexChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& sender,
            winrt::Windows::UI::Xaml::DependencyProperty const& indexProperty
        );
        void onSelectionModeChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& sender,
            winrt::Windows::UI::Xaml::DependencyProperty const& indexProperty
        );
        void onHorizontalAlignmentChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& sender,
            winrt::Windows::UI::Xaml::DependencyProperty const& horizontalAlignmentProperty
        );
        void onItemsPanelChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& sender,
            winrt::Windows::UI::Xaml::DependencyProperty const& itemsPanelProperty
        );

        void setMultiSelectStyle(bool value);

        winrt::Windows::UI::Xaml::Controls::Border m_knob{ nullptr };

        winrt::Windows::UI::Xaml::Media::Animation::DoubleAnimation m_knobTranslateXAnimation{ nullptr };
        winrt::Windows::UI::Xaml::Media::Animation::DoubleAnimation m_knobTranslateYAnimation{ nullptr };

        winrt::Windows::UI::Xaml::Media::Animation::DoubleAnimation m_knobWidthAnimation{ nullptr };
        winrt::Windows::UI::Xaml::Media::Animation::DoubleAnimation m_knobHeightAnimation{ nullptr };

        winrt::Windows::UI::Xaml::Media::Animation::Storyboard m_knobAnimation{ nullptr };
        winrt::Windows::UI::Xaml::FrameworkElement::SizeChanged_revoker m_knobSizeChangeRevoker;

        bool m_isFirst = true;
        bool m_isMultiSelect = false;
        int m_internalSelectedIndex = -1;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct Segmented : SegmentedT<Segmented, implementation::Segmented>
    {
    };
}
