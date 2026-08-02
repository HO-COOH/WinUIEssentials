#pragma once

#include "WebView.g.h"
#include <winrt/Windows.Web.UI.Interop.h>

namespace winrt::WinUI3Package::implementation
{
    struct WebView : WebViewT<WebView>
    {
        WebView();

        bool CanGoBack();
        static winrt::Microsoft::UI::Xaml::DependencyProperty CanGoBackProperty();

        bool CanGoForward();
        static winrt::Microsoft::UI::Xaml::DependencyProperty CanGoForwardProperty();

        bool ContainsFullScreenElement();
        static winrt::Microsoft::UI::Xaml::DependencyProperty ContainsFullScreenElementProperty();

        winrt::Windows::UI::Color DefaultBackgroundColor();
        void DefaultBackgroundColor(winrt::Windows::UI::Color value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty DefaultBackgroundColorProperty();

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Controls::WebViewDeferredPermissionRequest> DeferredPermissionRequests();

        winrt::hstring DocumentTitle();
        static winrt::Microsoft::UI::Xaml::DependencyProperty DocumentTitleProperty();

        winrt::Windows::UI::Xaml::Controls::WebViewSettings Settings();

        winrt::Windows::Foundation::Uri Source();
        void Source(winrt::Windows::Foundation::Uri const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty SourceProperty();
    private:
        winrt::Windows::Web::UI::Interop::WebViewControlProcess m_process;
        winrt::Windows::Web::UI::Interop::WebViewControl m_webview{ nullptr };
        winrt::Windows::Foundation::Rect m_cachedBounds{};

        winrt::fire_and_forget onLoaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args
        );

        winrt::Windows::Foundation::Rect getBounds(double scale);

        inline static winrt::Microsoft::UI::Xaml::DependencyProperty s_canGoBackProperty{ nullptr };

    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WebView : WebViewT<WebView, implementation::WebView>
    {
    };
}
