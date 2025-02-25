#include "pch.h"
#include "ImageExtension.h"
#if __has_include("ImageExtension.g.cpp")
#include "ImageExtension.g.cpp"
#endif
#include "UnsupportedImageTypeError.hpp"

namespace winrt::UWPPackage::implementation
{
    winrt::Windows::UI::Xaml::DependencyProperty ImageExtension::s_fallbackProperty =
        winrt::Windows::UI::Xaml::DependencyProperty::RegisterAttached(
            L"FallbackSource",
            winrt::xaml_typename<winrt::Windows::UI::Xaml::Media::ImageSource>(),
            winrt::xaml_typename<class_type>(),
            nullptr
        );
    winrt::Windows::UI::Xaml::DependencyProperty ImageExtension::FallbackSourceProperty()
    {
        return s_fallbackProperty;
    }
    void ImageExtension::SetFallbackSource(
        winrt::Windows::UI::Xaml::DependencyObject const& image,
        winrt::Windows::UI::Xaml::Media::ImageSource const& source)
    {
        image.SetValue(FallbackSourceProperty(), source);
        if (auto imageControl = image.try_as<winrt::Windows::UI::Xaml::Controls::Image>())
        {
            imageControl.ImageFailed([image = winrt::make_weak(imageControl)](auto&&...)
                {
                    if (auto strongImage = image.get())
                    {
                        strongImage.Source(GetFallbackSource(strongImage));
                    }
                });
        }
        else
            throw UnsupportedImageTypeError{};
    }

    winrt::Windows::UI::Xaml::Media::ImageSource ImageExtension::GetFallbackSource(
        winrt::Windows::UI::Xaml::DependencyObject const& image)
    {
        return image.GetValue(FallbackSourceProperty()).as<winrt::Windows::UI::Xaml::Media::ImageSource>();
    }
}
