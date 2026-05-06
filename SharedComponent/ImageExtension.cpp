#include "pch.h"
#include "ImageExtension.h"
#if __has_include("ImageExtension.g.cpp")
#include "ImageExtension.g.cpp"
#endif

namespace winrt::PackageRoot::implementation
{
    winrt::WinUINamespace::UI::Xaml::DependencyProperty ImageExtension::FallbackSourceProperty()
    {
        static auto s_fallbackProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::RegisterAttached(
            L"FallbackSource",
            winrt::xaml_typename<winrt::WinUINamespace::UI::Xaml::Media::ImageSource>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{ nullptr, &ImageExtension::fallbackSourceChanged }
        );
        return s_fallbackProperty;
    }

    void ImageExtension::SetFallbackSource(
        winrt::WinUINamespace::UI::Xaml::Controls::Image const& image,
        winrt::WinUINamespace::UI::Xaml::Media::ImageSource const& source)
    {
        image.SetValue(FallbackSourceProperty(), source);
    }

    winrt::WinUINamespace::UI::Xaml::Media::ImageSource ImageExtension::GetFallbackSource(winrt::WinUINamespace::UI::Xaml::Controls::Image const& image)
    {
        return image.GetValue(FallbackSourceProperty()).as<winrt::WinUINamespace::UI::Xaml::Media::ImageSource>();
    }

    void ImageExtension::fallbackSourceChanged(winrt::WinUINamespace::UI::Xaml::DependencyObject const& image, winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto newValue = e.NewValue();
        if (!newValue)
            return;

		auto imageSource = newValue.try_as<winrt::WinUINamespace::UI::Xaml::Media::ImageSource>();
        if (!imageSource)
            return;

        image.as<winrt::WinUINamespace::UI::Xaml::Controls::Image>().ImageFailed([imageSource](winrt::Windows::Foundation::IInspectable const& sender, auto&&)
        {
            if (auto strongImage = sender.try_as<winrt::WinUINamespace::UI::Xaml::Controls::Image>())
            {
                strongImage.Source(imageSource);
            }
        });
    }
}
