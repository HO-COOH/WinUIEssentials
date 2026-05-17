#pragma once

#include "SvgImageSource.g.h"
#include "../WinUI3Package/include/EnsureDependencyProperty.hpp"
#include <resvg.h>
#include <mutex>
#include <variant>
#include "RenderTree.h"

namespace winrt::WinUI3Package::Svg::implementation
{
    struct SvgImageSource : SvgImageSourceT<SvgImageSource>, EnsureDependencyProperty<SvgImageSource>
    {
        static void EnsureDependencyProperties();

        SvgImageSource() = default;

        winrt::Windows::Foundation::IInspectable UriSource() const;
        void UriSource(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty UriSourceProperty();

        winrt::hstring StringSource();
        void StringSource(winrt::hstring const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty StringSourceProperty();

        double RasterizePixelWidth() const;
        void RasterizePixelWidth(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty RasterizePixelWidthProperty();

        double RasterizePixelHeight() const;
        void RasterizePixelHeight(double value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty RasterizePixelHeightProperty();

        void BindSizeTo(winrt::Microsoft::UI::Xaml::Controls::Image const& image);
        winrt::Microsoft::UI::Xaml::Controls::Image BindSizeTo();
    private:
        winrt::Microsoft::UI::Xaml::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker;
        // weak_ref breaks the otherwise-circular Image.Source -> SvgImageSource -> Image chain.
        winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::Image> m_boundImage;

        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_uriSourceProperty{ nullptr };
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_stringSourceProperty{ nullptr };
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_rasterizePixelWidthProperty{ nullptr };
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_rasterizePixelHeightProperty{ nullptr };

        std::variant<std::monostate, winrt::Windows::Foundation::Uri, winrt::hstring> m_currentSource;
        std::mutex m_treeMutex;
        resvg::RenderTree m_tree;
        winrt::Windows::Foundation::IAsyncAction m_currentOp{ nullptr };

        static void onUriSourceChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onRasterizeSizeChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onStringSourceChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        // Cancel m_currentOp (if still Started) and replace it with `next`.
        // Caller must already be on the UI thread.
        void replaceOp(winrt::Windows::Foundation::IAsyncAction next);

        winrt::Windows::Foundation::IAsyncAction loadFromUri(winrt::Windows::Foundation::Uri uri);
        winrt::Windows::Foundation::IAsyncAction loadFromString(winrt::hstring str);
        winrt::Windows::Foundation::IAsyncAction renderAsync(double rasterWidth, double rasterHeight);

        struct ScaleResult
        {
            float scale;
            uint32_t width;
            uint32_t height;
        };

        static resvg_options* GetResvgOptions();

        constexpr static auto getUniformScale(double rasterWidth, double rasterHeight, float naturalWidth, float naturalHeight)
        {
            float scale = 1.0f;
            if (rasterWidth > 0.0 || rasterHeight > 0.0)
            {
                float scaleX = (rasterWidth > 0.0) ? static_cast<float>(rasterWidth) / static_cast<float>(naturalWidth) : std::numeric_limits<float>::infinity();
                float scaleY = (rasterHeight > 0.0) ? static_cast<float>(rasterHeight) / static_cast<float>(naturalHeight) : std::numeric_limits<float>::infinity();
                scale = (std::min)(scaleX, scaleY);
                return ScaleResult
                {
                    .scale = scale,
                    .width = static_cast<uint32_t>(std::ceil(naturalWidth * scale)),
                    .height = static_cast<uint32_t>(std::ceil(naturalHeight * scale))
                };
            }
            return ScaleResult{ scale, static_cast<uint32_t>(naturalWidth), static_cast<uint32_t>(naturalHeight) };
        }

        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IBuffer> getSvgContent(winrt::Windows::Foundation::Uri uri);
    };
}

namespace winrt::WinUI3Package::Svg::factory_implementation
{
    struct SvgImageSource : SvgImageSourceT<SvgImageSource, implementation::SvgImageSource>
    {
    };
}
