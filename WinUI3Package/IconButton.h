#pragma once

#include "IconButton.g.h"
#include <optional>
#include <winrt/Microsoft.UI.Xaml.Media.Animation.h>

namespace winrt::WinUI3Package::implementation
{
    struct IconButton : IconButtonT<IconButton>
    {
        IconButton();

        void OnApplyTemplate();

        winrt::Windows::Foundation::IInspectable Icon();
        void Icon(winrt::Windows::Foundation::IInspectable value);

        static winrt::Microsoft::UI::Xaml::DependencyProperty IconProperty();

        void Collapse();
        void Expand();

        bool IsExpanded();
        void IsExpanded(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty IsExpandedProperty();

        winrt::Microsoft::UI::Xaml::Controls::Primitives::ButtonBase Container();
        void Container(winrt::Microsoft::UI::Xaml::Controls::Primitives::ButtonBase value);
    private:
        winrt::Microsoft::UI::Xaml::Controls::Primitives::ButtonBase m_container{ nullptr };

        static void isExpandedPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs args
        );
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_iconProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty m_isExpandedProperty;
        winrt::Microsoft::UI::Xaml::Media::Animation::Storyboard m_storyboard{ nullptr };
        winrt::Microsoft::UI::Xaml::Media::Animation::DoubleAnimation m_widthAnimation{ nullptr };
        winrt::Microsoft::UI::Xaml::Controls::ContentPresenter m_iconContent{ nullptr };
        winrt::Microsoft::UI::Xaml::Controls::ContentPresenter m_contentPresenter{ nullptr };
        std::optional<double> m_firstWidth;
        constexpr static std::chrono::milliseconds duration{ 300 };
        bool m_loaded{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct IconButton : IconButtonT<IconButton, implementation::IconButton>
    {
    };
}
