#pragma once

#include "SvgPage.g.h"

namespace winrt::UWPExample::implementation
{
    struct SvgPage : SvgPageT<SvgPage>
    {

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Svgs();

        static winrt::Windows::Foundation::Uri GetPngFromSvgUrl(winrt::hstring const& svgUrl);
        static winrt::Windows::UI::Xaml::Media::ImageSource GetPngBitmapFromSvgUrl(winrt::hstring const& svgUrl);
        static winrt::Windows::UI::Xaml::Media::ImageSource GetSvgImageSourceFromString(winrt::hstring const& svgContent);
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_svgs{ nullptr };
    public:
        void Image_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::ExceptionRoutedEventArgs const& e);
    };
}

namespace winrt::UWPExample::factory_implementation
{
    struct SvgPage : SvgPageT<SvgPage, implementation::SvgPage>
    {
    };
}
