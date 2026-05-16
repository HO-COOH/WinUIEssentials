#include "pch.h"
#include "SvgImageSource.h"
#include "SvgImageSource.g.cpp"

#include <winrt/Windows.Web.Http.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Graphics.Imaging.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>

#include <resvg.h>

#include <cmath>
#include <string>
#include <vector>

namespace winrt::WinUI3Package::Svg::implementation
{
    namespace
    {
        // resvg's options carry the parsed font database. System-font discovery is heavy
        // I/O, so we do it once per process and reuse the options across renders.
        resvg_options* GetResvgOptions()
        {
            static resvg_options* opts = []() {
                resvg_init_log();
                auto* o = resvg_options_create();
                resvg_options_load_system_fonts(o);
                return o;
            }();
            return opts;
        }
    }

    winrt::Microsoft::UI::Xaml::DependencyProperty SvgImageSource::UriSourceProperty()
    {
        static auto prop = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
            L"UriSource",
            winrt::xaml_typename<winrt::Windows::Foundation::Uri>(),
            winrt::xaml_typename<winrt::WinUI3Package::Svg::SvgImageSource>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                winrt::Microsoft::UI::Xaml::PropertyChangedCallback{ &SvgImageSource::OnUriSourceChanged }
            });
        return prop;
    }

    winrt::Windows::Foundation::IInspectable SvgImageSource::UriSource() const
    {
        return const_cast<SvgImageSource*>(this)->GetValue(UriSourceProperty());
    }

    void SvgImageSource::UriSource(winrt::Windows::Foundation::IInspectable const& value)
    {
        // XAML hands us different shapes for custom IDL types: an unresolved Binding
        // markup, a Uri, or a boxed string. Route each to the DP so OnUriSourceChanged
        // drives the load.
        if (auto binding = value.try_as<winrt::Microsoft::UI::Xaml::Data::Binding>())
        {
            auto self = get_strong().as<winrt::Microsoft::UI::Xaml::DependencyObject>();
            winrt::Microsoft::UI::Xaml::Data::BindingOperations::SetBinding(
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

    void SvgImageSource::OnUriSourceChanged(
        winrt::Microsoft::UI::Xaml::DependencyObject const& d,
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
    {
        auto self = winrt::get_self<SvgImageSource>(
            d.as<winrt::WinUI3Package::Svg::SvgImageSource>());

        auto uri = e.NewValue().try_as<winrt::Windows::Foundation::Uri>();
        if (!uri)
            return;

        self->SetSourceUriAsync(uri);
    }

    void SvgImageSource::SetSourceText(winrt::hstring const& svgXml)
    {
        auto myToken = ++m_loadToken;
        std::string utf8 = winrt::to_string(svgXml);
        std::vector<uint8_t> bytes(utf8.begin(), utf8.end());
        RenderAndApplyAsync(std::move(bytes), myToken);
    }

    winrt::Windows::Foundation::IAsyncAction SvgImageSource::SetSourceUriAsync(winrt::Windows::Foundation::Uri uri)
    {
        auto strong = get_strong();
        auto myToken = ++strong->m_loadToken;

        winrt::Windows::Web::Http::HttpClient client;
        auto buffer = co_await client.GetBufferAsync(uri);

        if (myToken != strong->m_loadToken)
            co_return;

        auto reader = winrt::Windows::Storage::Streams::DataReader::FromBuffer(buffer);
        auto size = buffer.Length();
        std::vector<uint8_t> bytes(size);
        if (size > 0)
            reader.ReadBytes(bytes);

        if (myToken != strong->m_loadToken)
            co_return;

        strong->RenderAndApplyAsync(std::move(bytes), myToken);
    }

    winrt::fire_and_forget SvgImageSource::RenderAndApplyAsync(std::vector<uint8_t> data, uint64_t token)
    {
        auto strong = get_strong();
        // Capture the UI dispatcher so we can hop back at the very end. Doing the SVG
        // parse + raster + PNG encode on the UI thread piles up apartment-resume
        // callbacks (one per outstanding SVG) and exhausts the STA stack when many
        // SvgImageSources are loading at once.
        auto dispatcher = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();

        try
        {
            co_await winrt::resume_background();

            // 1. Parse SVG with resvg.
            resvg_render_tree* tree = nullptr;
            int32_t err = resvg_parse_tree_from_data(
                reinterpret_cast<char const*>(data.data()),
                data.size(),
                GetResvgOptions(),
                &tree);
            if (err != RESVG_OK || !tree)
                co_return;

            auto svgSize = resvg_get_image_size(tree);
            uint32_t w = static_cast<uint32_t>(std::ceil(svgSize.width));
            uint32_t h = static_cast<uint32_t>(std::ceil(svgSize.height));
            if (w == 0 || h == 0)
            {
                resvg_tree_destroy(tree);
                co_return;
            }

            // 2. Render into a width*height*4 premultiplied-RGBA buffer.
            std::vector<uint8_t> pixels(static_cast<size_t>(w) * h * 4, 0);
            resvg_render(
                tree,
                resvg_transform_identity(),
                w, h,
                reinterpret_cast<char*>(pixels.data()));
            resvg_tree_destroy(tree);

            // 3. PNG-encode via WIC's BitmapEncoder. (BitmapSource only ingests an encoded
            // image stream — it doesn't accept a raw pixel buffer directly.)
            using namespace winrt::Windows::Graphics::Imaging;
            using namespace winrt::Windows::Storage::Streams;

            InMemoryRandomAccessStream rastream;
            auto encoder = co_await BitmapEncoder::CreateAsync(BitmapEncoder::PngEncoderId(), rastream);
            encoder.SetPixelData(
                BitmapPixelFormat::Rgba8,
                BitmapAlphaMode::Premultiplied,
                w, h,
                96.0, 96.0,
                winrt::array_view<uint8_t const>{ pixels.data(), pixels.data() + pixels.size() });
            co_await encoder.FlushAsync();
            rastream.Seek(0);

            if (token != strong->m_loadToken)
                co_return;

            // 4. Hop back to the UI thread to feed our BitmapSource base class.
            if (dispatcher)
                co_await wil::resume_foreground(dispatcher);

            co_await strong->SetSourceAsync(rastream);
        }
        catch (...)
        {
            // Fire-and-forget must not propagate exceptions out of the coroutine.
        }
    }
}
