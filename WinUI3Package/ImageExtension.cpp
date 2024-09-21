#include "pch.h"
#include "ImageExtension.h"
#if __has_include("ImageExtension.g.cpp")
#include "ImageExtension.g.cpp"
#endif
#include "UnsupportedImageTypeError.hpp"

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty ImageExtension::s_fallbackProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"FallbackSource",
            winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Media::ImageSource>(),
            winrt::xaml_typename<class_type>(),
            nullptr
        );
    winrt::Microsoft::UI::Xaml::DependencyProperty ImageExtension::FallbackSourceProperty()
    {
        return s_fallbackProperty;
    }
    void ImageExtension::SetFallbackSource(
        winrt::Microsoft::UI::Xaml::DependencyObject const& image,
        winrt::Microsoft::UI::Xaml::Media::ImageSource const& source)
    {
        image.SetValue(FallbackSourceProperty(), source);
        if (auto imageControl = image.try_as<winrt::Microsoft::UI::Xaml::Controls::Image>())
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

    winrt::Microsoft::UI::Xaml::Media::ImageSource ImageExtension::GetFallbackSource(
        winrt::Microsoft::UI::Xaml::DependencyObject const& image)
    {
        return image.GetValue(FallbackSourceProperty()).as<winrt::Microsoft::UI::Xaml::Media::ImageSource>();
    }
}
