#pragma once

#include "EqualPanel.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include <ranges>

namespace winrt::PackageRoot::implementation
{
    struct EqualPanel : EqualPanelT<EqualPanel>, EnsureDependencyProperty<EqualPanel>
    {
        static void EnsureDependencyProperties();
        EqualPanel();

        double HorizontalSpacing();
        void HorizontalSpacing(double value);

        double VerticalSpacing();
        void VerticalSpacing(double value);

        winrt::WinUINamespace::UI::Xaml::Controls::Orientation Orientation();
        void Orientation(winrt::WinUINamespace::UI::Xaml::Controls::Orientation value);

        static winrt::WinUINamespace::UI::Xaml::DependencyProperty HorizontalSpacingProperty();
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty VerticalSpacingProperty();
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty OrientationProperty();

        winrt::Windows::Foundation::Size MeasureOverride(winrt::Windows::Foundation::Size availableSize);
        winrt::Windows::Foundation::Size ArrangeOverride(winrt::Windows::Foundation::Size finalSize);
    private:
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_horizontalSpacingProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_verticalSpacingProperty = nullptr;
        static inline winrt::WinUINamespace::UI::Xaml::DependencyProperty s_orientationProperty = nullptr;
        bool hasMoreSpaceAvailable(winrt::Windows::Foundation::Size availableSize);
        auto filterVisibleChildren() const
        {
            return Children() | std::views::filter([](auto element) { return element.Visibility() == winrt::WinUINamespace::UI::Xaml::Visibility::Visible; });
        }

        void onHorizontalAlignmentChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& sender,
            winrt::WinUINamespace::UI::Xaml::DependencyProperty const& horizontalAlignmentProperity
        );
        float m_maxItemHeight{};
        float m_maxItemWidth{};
        int m_visibleItemsCount{};
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct EqualPanel : EqualPanelT<EqualPanel, implementation::EqualPanel>
    {
    };
}
