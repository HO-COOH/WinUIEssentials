#pragma once

#include "ImageExtension.g.h"
#include <winrt/Microsoft.UI.Xaml.Media.h>

namespace winrt::WinUI3Package::implementation
{
    struct ImageExtension : ImageExtensionT<ImageExtension>
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty FallbackSourceProperty();
        
        static void SetFallbackSource(
            winrt::Microsoft::UI::Xaml::DependencyObject const& image,
            winrt::Microsoft::UI::Xaml::Media::ImageSource const& source);
        
        static winrt::Microsoft::UI::Xaml::Media::ImageSource GetFallbackSource(
            winrt::Microsoft::UI::Xaml::DependencyObject const& image
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ImageExtension : ImageExtensionT<ImageExtension, implementation::ImageExtension>
    {
    };
}
