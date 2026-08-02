#pragma once

#include "WebView.g.h"
#include <winrt/Windows.Web.UI.h>
#include <winrt/Windows.Web.UI.Interop.h>
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
	struct WebView : WebViewT<WebView>, EnsureDependencyProperty<WebView>
    {
		static void EnsureDependencyProperties();

        WebView();

#pragma region Properties
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

        winrt::Windows::Web::UI::WebViewControlSettings Settings();

        winrt::Windows::Foundation::Uri Source();
        void Source(winrt::Windows::Foundation::Uri const& value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty SourceProperty();
#pragma endregion
#pragma region Events
        winrt::event_token ContentLoading(
            winrt::Windows::Foundation::TypedEventHandler<
                winrt::WinUI3Package::WebView, 
                winrt::Windows::Web::UI::WebViewControlContentLoadingEventArgs
            > const& handler
        );
		void ContentLoading(winrt::event_token const& token);

		winrt::event_token DOMContentLoaded(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlDOMContentLoadedEventArgs> const& handler);
		void DOMContentLoaded(winrt::event_token const& token);

		winrt::event_token FrameContentLoading(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlContentLoadingEventArgs> const& handler);
		void FrameContentLoading(winrt::event_token const& token);

		winrt::event_token FrameDOMContentLoaded(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlDOMContentLoadedEventArgs> const& handler);
		void FrameDOMContentLoaded(winrt::event_token const& token);

		winrt::event_token FrameNavigationStarting(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationStartingEventArgs> const& handler);
		void FrameNavigationStarting(winrt::event_token const& token);

		winrt::event_token MoveFocusRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusRequestedEventArgs> const& handler);
		void MoveFocusRequested(winrt::event_token const& token);

		winrt::event_token LongRunningScriptDetected(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlLongRunningScriptDetectedEventArgs> const& handler);
		void LongRunningScriptDetected(winrt::event_token const& token);

		winrt::event_token NavigationStarting(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationStartingEventArgs> const& handler);
		void NavigationStarting(winrt::event_token const& token);

		winrt::event_token NavigationCompleted(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationCompletedEventArgs> const& handler);
		void NavigationCompleted(winrt::event_token const& token);

		winrt::event_token NewWindowRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNewWindowRequestedEventArgs> const& handler);
		void NewWindowRequested(winrt::event_token const& token);

		winrt::event_token PermissionRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlPermissionRequestedEventArgs> const& handler);
		void PermissionRequested(winrt::event_token const& token);

		winrt::event_token ScriptNotify(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlScriptNotifyEventArgs> const& handler);
		void ScriptNotify(winrt::event_token const& token);

		winrt::event_token UnsafeContentWarningDisplaying(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Foundation::IInspectable> const& handler);
		void UnsafeContentWarningDisplaying(winrt::event_token const& token);

		winrt::event_token UnsupportedUriSchemeIdentified(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlUnsupportedUriSchemeIdentifiedEventArgs> const& handler);
		void UnsupportedUriSchemeIdentified(winrt::event_token const& token);

		winrt::event_token UnviewableContentIdentified(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlUnviewableContentIdentifiedEventArgs> const& handler);
		void UnviewableContentIdentified(winrt::event_token const& token);

		winrt::event_token WebResourceRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlWebResourceRequestedEventArgs> const& handler);
		void WebResourceRequested(winrt::event_token const& token);
#pragma endregion
#pragma region Methods
        void AddInitializeScript(winrt::hstring const& script);
        winrt::Windows::Foundation::Uri BuildLocalStreamUri(winrt::hstring const& contentIdentifier, winrt::hstring const& relativePath);
		winrt::Windows::Foundation::IAsyncAction CapturePreviewToStreamAsync(winrt::Windows::Storage::Streams::IRandomAccessStream stream);
		winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::ApplicationModel::DataTransfer::DataPackage> CaptureSelectedContentToDataPackageAsync();
        void Close();
		void GetDeferredPermissionRequestById(uint32_t id, winrt::Windows::Web::UI::WebViewControlDeferredPermissionRequest& request);
        void GoBack();
        void GoForward();
		winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> InvokeScriptAsync(winrt::hstring scriptName, winrt::Windows::Foundation::Collections::IIterable<winrt::hstring> arguments);
		void MoveFocus(winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusReason const& reason);
		void Navigate(winrt::Windows::Foundation::Uri const& source);
		void NavigateToLocalStreamUri(winrt::Windows::Foundation::Uri const& source, winrt::Windows::Web::IUriToStreamResolver const& streamResolver);
		void NavigateToString(winrt::hstring const& text);
		void NavigateWithHttpRequestMessage(winrt::Windows::Web::Http::HttpRequestMessage const& requestMessage);
		void Refresh();
		void Stop();
#pragma endregion

    private:
        winrt::Windows::Web::UI::Interop::WebViewControlProcess m_process;
        winrt::Windows::Web::UI::Interop::WebViewControl m_webview{ nullptr };
        winrt::Windows::Foundation::Rect m_cachedBounds{};
        winrt::handle m_loaded{ ::CreateEventW(nullptr, true /*manual reset*/, false, nullptr) };

        winrt::event<winrt::Windows::Foundation::TypedEventHandler<
            winrt::WinUI3Package::WebView,
            winrt::Windows::Web::UI::WebViewControlContentLoadingEventArgs
        >> m_contentLoading;

        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlDOMContentLoadedEventArgs>> m_domContentLoaded;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlContentLoadingEventArgs>> m_frameContentLoading;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlDOMContentLoadedEventArgs>> m_frameDOMContentLoaded;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationStartingEventArgs>> m_frameNavigationStarting;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusRequestedEventArgs>> m_moveFocusRequested;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlLongRunningScriptDetectedEventArgs>> m_longRunningScriptDetected;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationStartingEventArgs>> m_navigationStarting;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationCompletedEventArgs>> m_navigationCompleted;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNewWindowRequestedEventArgs>> m_newWindowRequested;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlPermissionRequestedEventArgs>> m_permissionRequested;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlScriptNotifyEventArgs>> m_scriptNotify;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Foundation::IInspectable>> m_unsafeContentWarningDisplaying;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlUnsupportedUriSchemeIdentifiedEventArgs>> m_unsupportedUriSchemeIdentified;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlUnviewableContentIdentifiedEventArgs>> m_unviewableContentIdentified;
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlWebResourceRequestedEventArgs>> m_webResourceRequested;

        winrt::fire_and_forget onLoaded(
            winrt::Windows::Foundation::IInspectable const& sender,
            winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args
        );

        void setProperties();

        // Completes immediately if m_webview is already created; otherwise suspends until
        // onLoaded signals m_loaded, then resumes on the UI thread.
        winrt::Windows::Foundation::IAsyncAction waitForLoadAsync();

        winrt::Windows::Foundation::Rect getBounds(double scale);

        static winrt::Microsoft::UI::Xaml::DependencyProperty s_canGoBackProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_canGoForwardProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_containsFullScreenElementProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_defaultBackgroundColorProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_documentTitleProperty;
		static winrt::Microsoft::UI::Xaml::DependencyProperty s_sourceProperty;

		static void onDefaultBackgroundColorChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d,
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);

		static void onSourceChanged(
			winrt::Microsoft::UI::Xaml::DependencyObject const& d,
			winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
		);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct WebView : WebViewT<WebView, implementation::WebView>
    {
    };
}
