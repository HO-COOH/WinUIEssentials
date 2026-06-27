#pragma once

#include "SvgPage.g.h"

namespace winrt::WinUI3Example::implementation
{
    struct SvgPage : SvgPageT<SvgPage>
    {
        SvgPage() = default;

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> Svgs();

        static winrt::Windows::Foundation::Uri GetPngFromSvgUrl(winrt::Windows::Foundation::IInspectable const& svgUrl);
        static winrt::Microsoft::UI::Xaml::Media::ImageSource GetSvgImageSourceFromString(winrt::hstring const& svgContent);
    private:
        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> m_svgs{ nullptr };
    public:
        void Image_ImageFailed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::ExceptionRoutedEventArgs const& e);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct SvgPage : SvgPageT<SvgPage, implementation::SvgPage>
    {
    };
}
