#pragma once

#include "SvgImageSource.g.h"

#include <vector>

namespace winrt::WinUI3Package::Svg::implementation
{
    struct SvgImageSource : SvgImageSourceT<SvgImageSource>
    {
        SvgImageSource() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty UriSourceProperty();

        winrt::Windows::Foundation::IInspectable UriSource() const;
        void UriSource(winrt::Windows::Foundation::IInspectable const& value);

        void SetSourceText(winrt::hstring const& svgXml);
        winrt::Windows::Foundation::IAsyncAction SetSourceUriAsync(winrt::Windows::Foundation::Uri uri);

    private:
        uint64_t m_loadToken{ 0 };

        static void OnUriSourceChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e);

        winrt::fire_and_forget RenderAndApplyAsync(std::vector<uint8_t> data, uint64_t token);
    };
}

namespace winrt::WinUI3Package::Svg::factory_implementation
{
    struct SvgImageSource : SvgImageSourceT<SvgImageSource, implementation::SvgImageSource>
    {
    };
}
