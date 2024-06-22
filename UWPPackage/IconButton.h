#pragma once

#include "IconButton.g.h"
#include "include/TemplateControlHelper.hpp"

namespace winrt::UWPPackage::implementation
{
    struct IconButton : IconButtonT<IconButton>, TemplateControlHelper<IconButton>
    {
        IconButton();

        void OnApplyTemplate();

        winrt::Windows::Foundation::IInspectable Icon();
        void Icon(winrt::Windows::Foundation::IInspectable value);

        static winrt::Windows::UI::Xaml::DependencyProperty IconProperty();

        void Collapse();
        void Expand();

        bool IsExpanded();
        void IsExpanded(bool value);
        static winrt::Windows::UI::Xaml::DependencyProperty IsExpandedProperty();

        winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase Container();
        void Container(winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase value);
    private:
        winrt::Windows::UI::Xaml::Controls::Primitives::ButtonBase m_container{ nullptr };

        static void isExpandedPropertyChanged(
            winrt::Windows::UI::Xaml::DependencyObject d,
            winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs args
        );
        static winrt::Windows::UI::Xaml::DependencyProperty m_iconProperty;
        static winrt::Windows::UI::Xaml::DependencyProperty m_isExpandedProperty;
        winrt::Windows::UI::Xaml::Media::Animation::Storyboard m_storyboard{ nullptr };
        winrt::Windows::UI::Xaml::Media::Animation::DoubleAnimation m_widthAnimation{ nullptr };
        winrt::Windows::UI::Xaml::Controls::ContentPresenter m_iconContent{ nullptr };
        winrt::Windows::UI::Xaml::Controls::ContentPresenter m_contentPresenter{ nullptr };
        std::optional<double> m_firstWidth;
        constexpr static std::chrono::milliseconds duration{ 300 };
        bool m_loaded{};
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct IconButton : IconButtonT<IconButton, implementation::IconButton>
    {
    };
}
