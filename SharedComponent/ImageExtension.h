#pragma once

#include "ImageExtension.g.h"
#include <winrt/Microsoft.UI.Xaml.Media.h>

namespace winrt::PackageRoot::implementation
{
    struct ImageExtension : ImageExtensionT<ImageExtension>
    {
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty FallbackSourceProperty();
        
        static void SetFallbackSource(
            winrt::WinUINamespace::UI::Xaml::Controls::Image const& image,
            winrt::WinUINamespace::UI::Xaml::Media::ImageSource const& source);
        
        static winrt::WinUINamespace::UI::Xaml::Media::ImageSource GetFallbackSource(
            winrt::WinUINamespace::UI::Xaml::Controls::Image const& image
        );

    private:
        static void fallbackSourceChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& image,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::PackageRoot::factory_implementation
{
    struct ImageExtension : ImageExtensionT<ImageExtension, implementation::ImageExtension>
    {
    };
}
