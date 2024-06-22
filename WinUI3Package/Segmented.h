#pragma once

#include "Segmented.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct Segmented : SegmentedT<Segmented>, TemplateControlHelper<Segmented>
    {
        Segmented();

        void OnApplyTemplate();

        winrt::Windows::Foundation::Numerics::float2 SelectedItemActualWidth();
        winrt::Windows::Foundation::Numerics::float2 SelectedItemOffset();
    private:
        void onSelectedIndexChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& indexProperty
        );
        void onSelectionModeChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& indexProperty
        );
        void onHorizontalAlignmentChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& horizontalAlignmentProperty
        );
        void onItemsPanelChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyProperty const& itemsPanelProperty
        );

        void setMultiSelectStyle(bool value);

        winrt::Microsoft::UI::Xaml::Controls::Border m_knob{ nullptr };

        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_knobTranslateXAnimation{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_knobTranslateYAnimation{ nullptr };

        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_knobWidthAnimation{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_knobHeightAnimation{ nullptr };

        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard m_knobAnimation{ nullptr };
        winrt::Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker m_knobSizeChangeRevoker;

        bool m_isFirst = true;
        bool m_isMultiSelect = false;
        int m_internalSelectedIndex = -1;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct Segmented : SegmentedT<Segmented, implementation::Segmented>
    {
    };
}
