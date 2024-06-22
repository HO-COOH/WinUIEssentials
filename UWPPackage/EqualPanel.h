#pragma once

#include "EqualPanel.g.h"
#include <ranges>

namespace winrt::UWPPackage::implementation
{
    struct EqualPanel : EqualPanelT<EqualPanel>
    {
        EqualPanel();

        double HorizontalSpacing();
        void HorizontalSpacing(double value);

        double VerticalSpacing();
        void VerticalSpacing(double value);

        winrt::Windows::UI::Xaml::Controls::Orientation Orientation();
        void Orientation(winrt::Windows::UI::Xaml::Controls::Orientation value);

        static winrt::Windows::UI::Xaml::DependencyProperty HorizontalSpacingProperty();
        static winrt::Windows::UI::Xaml::DependencyProperty VerticalSpacingProperty();
        static winrt::Windows::UI::Xaml::DependencyProperty OrientationProperty();

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
    private:
        static winrt::Windows::UI::Xaml::DependencyProperty s_horizontalSpacingProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_verticalSpacingProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty s_orientationProperty;
        bool hasMoreSpaceAvailable(winrt::Windows::Foundation::Size availableSize);
        auto filterVisibleChildren() const
        {
            return Children() | std::views::filter([](auto element) { return element.Visibility() == winrt::Windows::UI::Xaml::Visibility::Visible; });
        }

        void onHorizontalAlignmentChanged(
            winrt::Windows::UI::Xaml::DependencyObject const& sender,
            winrt::Windows::UI::Xaml::DependencyProperty const& horizontalAlignmentProperity
        );
        float m_maxItemHeight{};
        float m_maxItemWidth{};
        int m_visibleItemsCount{};
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct EqualPanel : EqualPanelT<EqualPanel, implementation::EqualPanel>
    {
    };
}
