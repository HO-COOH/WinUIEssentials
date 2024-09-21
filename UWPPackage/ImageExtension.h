#pragma once

#include "ImageExtension.g.h"

namespace winrt::UWPPackage::implementation
{
    struct ImageExtension : ImageExtensionT<ImageExtension>
    {
        ImageExtension() = default;

        static winrt::Windows::UI::Xaml::DependencyProperty FallbackSourceProperty();

        static void SetFallbackSource(
            winrt::Windows::UI::Xaml::DependencyObject const& image,
            winrt::Windows::UI::Xaml::Media::ImageSource const& source);

        static winrt::Windows::UI::Xaml::Media::ImageSource GetFallbackSource(
            winrt::Windows::UI::Xaml::DependencyObject const& image
        );

        static winrt::Windows::UI::Xaml::DependencyProperty s_fallbackProperty;
    };
}

namespace winrt::UWPPackage::factory_implementation
{
    struct ImageExtension : ImageExtensionT<ImageExtension, implementation::ImageExtension>
    {
    };
}
