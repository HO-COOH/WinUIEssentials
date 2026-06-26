#include "pch.h"
#include "SvgImageSource.h"
#include "SvgImageSource.g.cpp"

#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#if defined Build_WinUIPackage
#include <winrt/Microsoft.UI.Xaml.Data.h>
#else
#include <winrt/Windows.UI.Xaml.Data.h>
#include <winrt/Windows.Graphics.Display.h>
#endif
#include <wil/resource.h>
#include <algorithm>
#include <cmath>
#include <limits>
#include "RenderTree.h"

static double getDpiScale(auto&& imageControl)
{
#if defined Build_WinUIPackage
    if (auto xamlRoot = image.XamlRoot())
        return xamlRoot.RasterizationScale();
    return 1.0;
#else
    winrt::Windows::Graphics::Display::DisplayInformation displayInfo = winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
    return displayInfo.RawPixelsPerViewPixel();
#endif
}

namespace winrt::PackageRoot::Svg::implementation
{
    resvg_options* SvgImageSource::GetResvgOptions()
    {
        static resvg_options* opts = []() {
            resvg_init_log();
            auto* o = resvg_options_create();
            resvg_options_load_system_fonts(o);
            return o;
        }();
        return opts;
    }

    void SvgImageSource::EnsureDependencyProperties()
    {
        if (s_uriSourceProperty) return;

        s_uriSourceProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"UriSource",
            winrt::xaml_typename<winrt::Windows::Foundation::Uri>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
                nullptr,
                winrt::WinUINamespace::UI::Xaml::PropertyChangedCallback{ &SvgImageSource::onUriSourceChanged }
            });

        s_rasterizePixelHeightProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"RasterizePixelHeight",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
                winrt::box_value(0.0),
                winrt::WinUINamespace::UI::Xaml::PropertyChangedCallback{ &SvgImageSource::onRasterizeSizeChanged }
            });

        s_rasterizePixelWidthProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"RasterizePixelWidth",
            winrt::xaml_typename<double>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
                winrt::box_value(0.0),
                winrt::WinUINamespace::UI::Xaml::PropertyChangedCallback{ &SvgImageSource::onRasterizeSizeChanged }
            });

        s_stringSourceProperty = winrt::WinUINamespace::UI::Xaml::DependencyProperty::Register(
            L"StringSource",
            winrt::xaml_typename<winrt::hstring>(),
            winrt::xaml_typename<class_type>(),
            winrt::WinUINamespace::UI::Xaml::PropertyMetadata{
                winrt::box_value(winrt::hstring{}),
                winrt::WinUINamespace::UI::Xaml::PropertyChangedCallback{ &SvgImageSource::onStringSourceChanged }
            });
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SvgImageSource::UriSourceProperty()
    {
        return s_uriSourceProperty;
    }

    winrt::hstring SvgImageSource::StringSource()
    {
        return winrt::unbox_value<winrt::hstring>(GetValue(s_stringSourceProperty));
    }

    void SvgImageSource::StringSource(winrt::hstring const& value)
    {
        SetValue(s_stringSourceProperty, winrt::box_value(value));
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SvgImageSource::StringSourceProperty()
    {
        return s_stringSourceProperty;
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SvgImageSource::RasterizePixelWidthProperty()
    {
        return s_rasterizePixelWidthProperty;
    }

    winrt::WinUINamespace::UI::Xaml::DependencyProperty SvgImageSource::RasterizePixelHeightProperty()
    {
        return s_rasterizePixelHeightProperty;
    }

    winrt::Windows::Foundation::IInspectable SvgImageSource::UriSource() const
    {
        return GetValue(s_uriSourceProperty);
    }

    void SvgImageSource::UriSource(winrt::Windows::Foundation::IInspectable const& value)
    {
        // XAML hands us different shapes for custom IDL types: an unresolved Binding
        // markup, a Uri, or a boxed string. Route each to the DP so OnUriSourceChanged
        // drives the load.
        if (auto binding = value.try_as<winrt::WinUINamespace::UI::Xaml::Data::Binding>())
        {
            auto self = get_strong().as<winrt::WinUINamespace::UI::Xaml::DependencyObject>();
            winrt::WinUINamespace::UI::Xaml::Data::BindingOperations::SetBinding(
                self, UriSourceProperty(), binding);
            return;
        }

        if (auto uri = value.try_as<winrt::Windows::Foundation::Uri>())
        {
            SetValue(UriSourceProperty(), uri);
            return;
        }

        winrt::hstring str;
        if (auto pv = value.try_as<winrt::Windows::Foundation::IPropertyValue>();
            pv && pv.Type() == winrt::Windows::Foundation::PropertyType::String)
        {
            str = pv.GetString();
        }
        if (!str.empty())
        {
            SetValue(UriSourceProperty(), winrt::Windows::Foundation::Uri{ str });
            return;
        }

        SetValue(UriSourceProperty(), nullptr);
    }

    double SvgImageSource::RasterizePixelWidth() const
    {
        return winrt::unbox_value<double>(GetValue(s_rasterizePixelWidthProperty));
    }

    void SvgImageSource::RasterizePixelWidth(double value)
    {
        SetValue(s_rasterizePixelWidthProperty, winrt::box_value(value));
    }

    double SvgImageSource::RasterizePixelHeight() const
    {
        return winrt::unbox_value<double>(GetValue(s_rasterizePixelHeightProperty));
    }

    void SvgImageSource::RasterizePixelHeight(double value)
    {
        SetValue(s_rasterizePixelHeightProperty, winrt::box_value(value));
    }

    void SvgImageSource::replaceOp(winrt::Windows::Foundation::IAsyncAction next)
    {
        if (m_currentOp && m_currentOp.Status() == winrt::Windows::Foundation::AsyncStatus::Started)
            m_currentOp.Cancel();
        m_currentOp = std::move(next);
    }

    void SvgImageSource::onUriSourceChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto uri = e.NewValue().try_as<winrt::Windows::Foundation::Uri>();
        if (!uri)
            return;

        auto self = winrt::get_self<SvgImageSource>(d.as<class_type>());
        self->m_currentSource = uri;
        self->replaceOp(self->loadFromUri(uri));
    }

    void SvgImageSource::onStringSourceChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto str = winrt::unbox_value_or<winrt::hstring>(e.NewValue(), winrt::hstring{});
        auto self = winrt::get_self<SvgImageSource>(d.as<class_type>());
        if (str.empty())
        {
            self->m_currentSource = std::monostate{};
            return;
        }
        self->m_currentSource = str;
        self->replaceOp(self->loadFromString(str));
    }

    void SvgImageSource::onRasterizeSizeChanged(
        winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
        winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const&)
    {
        auto self = winrt::get_self<SvgImageSource>(d.as<class_type>());
        if (self->m_isHandlingImageSizeChanged || std::holds_alternative<std::monostate>(self->m_currentSource))
            return;
        self->replaceOp(self->renderAsync(self->RasterizePixelWidth(), self->RasterizePixelHeight()));
    }

    winrt::Windows::Foundation::IAsyncAction SvgImageSource::loadFromUri(winrt::Windows::Foundation::Uri uri)
    {
        auto const rasterWidth = RasterizePixelWidth();
        auto const rasterHeight = RasterizePixelHeight();
        auto strong = get_strong();
        try
        {
            auto buffer = co_await getSvgContent(uri);
            {
                std::lock_guard lock(strong->m_treeMutex);
                if (!strong->m_tree.Parse(reinterpret_cast<char const*>(buffer.data()), buffer.Length(), GetResvgOptions()))
                    co_return;
            }

            co_await strong->renderAsync(rasterWidth, rasterHeight);
        }
        catch (...)
        {
        }
    }

    winrt::Windows::Foundation::IAsyncAction SvgImageSource::loadFromString(winrt::hstring str)
    {
        auto const rasterWidth = RasterizePixelWidth();
        auto const rasterHeight = RasterizePixelHeight();
        auto strong = get_strong();

        try
        {
            co_await winrt::resume_background();

            auto utf8 = winrt::to_string(str);
            {
                std::lock_guard lock(strong->m_treeMutex);
                if (!strong->m_tree.Parse(utf8.data(), utf8.size(), GetResvgOptions()))
                    co_return;
            }

            co_await strong->renderAsync(rasterWidth, rasterHeight);
        }
        catch (...)
        {
        }
    }

    winrt::Windows::Foundation::IAsyncAction SvgImageSource::renderAsync(double rasterWidth, double rasterHeight)
    {
        auto cancel = co_await winrt::get_cancellation_token();
        auto strong = get_strong();
        co_await winrt::resume_background();
        if (cancel())
            co_return;

        std::vector<uint8_t> pixels;
        uint32_t width = 0, height = 0;
        {
            std::lock_guard lock(strong->m_treeMutex);
            if (!strong->m_tree)
                co_return;

            auto [naturalWidth, naturalHeight] = strong->m_tree.GetSize();
            if (naturalWidth == 0 || naturalHeight == 0)
                co_return;

            auto scaled = getUniformScale(rasterWidth, rasterHeight, naturalWidth, naturalHeight);
            width = scaled.width;
            height = scaled.height;
            pixels = strong->m_tree.Render(scaled.scale, width, height);
        }

        if (cancel())
            co_return;

        winrt::Windows::Storage::Streams::InMemoryRandomAccessStream pngStream;
        auto encoder = co_await winrt::Windows::Graphics::Imaging::BitmapEncoder::CreateAsync(winrt::Windows::Graphics::Imaging::BitmapEncoder::PngEncoderId(), pngStream);
        encoder.SetPixelData(
            winrt::Windows::Graphics::Imaging::BitmapPixelFormat::Rgba8,
            winrt::Windows::Graphics::Imaging::BitmapAlphaMode::Premultiplied,
            width, height,
            96.0, 96.0,
            winrt::array_view<uint8_t const>{ pixels.data(), pixels.data() + pixels.size() });
        co_await encoder.FlushAsync();
        pngStream.Seek(0);

        if (cancel())
            co_return;

#if defined Build_WinUIPackage
        co_await wil::resume_foreground(strong->DispatcherQueue());
#else
        wil::resume_foreground(strong->Dispatcher());
#endif

        if (cancel())
            co_return;

        auto op = strong->SetSourceAsync(pngStream);
        op.Completed([](auto const&, auto) noexcept {});
    }

    void SvgImageSource::BindSizeTo(winrt::WinUINamespace::UI::Xaml::Controls::Image const& image)
    {
        m_boundImage = image;
        m_isHandlingImageSizeChanged = true;
        auto scopeExit = wil::scope_exit([&]() { m_isHandlingImageSizeChanged = false; });
        auto width = image.ActualWidth();
        auto height = image.ActualHeight();
        RasterizePixelWidth(width);
        RasterizePixelHeight(height);
		double const scale = getDpiScale(image);
        replaceOp(renderAsync(width * scale, height * scale));

        m_sizeChangedRevoker = image.SizeChanged(
            winrt::auto_revoke,
            [weakSelf = get_weak()](winrt::Windows::Foundation::IInspectable const& sender, winrt::WinUINamespace::UI::Xaml::SizeChangedEventArgs const& e)
            {
                auto self = weakSelf.get();
                if (!self)
                    return;

                self->m_isHandlingImageSizeChanged = true;
                auto scopeExit = wil::scope_exit([&]() { self->m_isHandlingImageSizeChanged = false; });
                if (std::holds_alternative<std::monostate>(self->m_currentSource))
                    return;
                auto image = sender.as<winrt::WinUINamespace::UI::Xaml::FrameworkElement>();
                double const scale = getDpiScale(image);
                
                auto [width, height] = e.NewSize();
                self->RasterizePixelWidth(width);
                self->RasterizePixelHeight(height);
                self->replaceOp(self->renderAsync(width * scale, height * scale));
            }
        );
    }

    winrt::WinUINamespace::UI::Xaml::Controls::Image SvgImageSource::BindSizeTo()
    {
        return m_boundImage.get();
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IBuffer> SvgImageSource::getSvgContent(winrt::Windows::Foundation::Uri uri)
    {
        static winrt::Windows::Web::Http::HttpClient httpClient;
        co_return co_await httpClient.GetBufferAsync(uri);
    }
}
