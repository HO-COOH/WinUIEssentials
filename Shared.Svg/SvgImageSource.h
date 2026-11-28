#pragma once

#include "SvgImageSource.g.h"
#if defined Build_WinUIPackage
#include "../WinUI3Package/include/EnsureDependencyProperty.hpp"
#else
#include "../UWPPackage/include/EnsureDependencyProperty.hpp"
#endif
#include <resvg.h>
#include <atomic>
#include <memory>
#include <variant>
#include "RenderTree.h"

namespace winrt::PackageRoot::Svg::implementation
{
    struct SvgImageSource : SvgImageSourceT<SvgImageSource>, EnsureDependencyProperty<SvgImageSource>
    {
        static void EnsureDependencyProperties();


        winrt::Windows::Foundation::IInspectable UriSource() const;
        void UriSource(winrt::Windows::Foundation::IInspectable const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty UriSourceProperty();

        winrt::hstring StringSource();
        void StringSource(winrt::hstring const& value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty StringSourceProperty();

        double RasterizePixelWidth() const;
        void RasterizePixelWidth(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty RasterizePixelWidthProperty();

        double RasterizePixelHeight() const;
        void RasterizePixelHeight(double value);
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty RasterizePixelHeightProperty();

        void BindSizeTo(winrt::WinUINamespace::UI::Xaml::Controls::Image const& image);
        winrt::WinUINamespace::UI::Xaml::Controls::Image BindSizeTo();
    private:
        bool m_isHandlingImageSizeChanged{};
        std::atomic<uint32_t> m_currentVersion{};
        std::atomic<uint32_t> m_renderVersion{};
        winrt::WinUINamespace::UI::Xaml::FrameworkElement::SizeChanged_revoker m_sizeChangedRevoker;
        // weak_ref breaks the otherwise-circular Image.Source -> SvgImageSource -> Image chain.
        winrt::weak_ref<winrt::WinUINamespace::UI::Xaml::Controls::Image> m_boundImage;

        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_uriSourceProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_stringSourceProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_rasterizePixelWidthProperty;
        static winrt::WinUINamespace::UI::Xaml::DependencyProperty s_rasterizePixelHeightProperty;

        std::variant<std::monostate, winrt::Windows::Foundation::Uri, winrt::hstring> m_currentSource;
        std::shared_ptr<resvg::RenderTree> m_tree;

        static void onUriSourceChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onRasterizeSizeChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
        static void onStringSourceChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );

        void renderCurrentTree();

        winrt::fire_and_forget loadFromUri(winrt::Windows::Foundation::Uri uri);
        winrt::fire_and_forget loadFromString(winrt::hstring str);
        winrt::fire_and_forget renderAsync(double rasterWidth, double rasterHeight);



        static resvg_options* GetResvgOptions();


        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IBuffer> getSvgContent(winrt::Windows::Foundation::Uri uri);
    };
}

namespace winrt::PackageRoot::Svg::factory_implementation
{
    struct SvgImageSource : SvgImageSourceT<SvgImageSource, implementation::SvgImageSource>
    {
    };
}
