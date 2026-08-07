#include "pch.h"
#include "WebView.h"
#if __has_include("WebView.g.cpp")
#include "WebView.g.cpp"
#endif
#include <include/HwndHelper.hpp>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")


constexpr static UINT_PTR kHostSubclassId = 0x57'42'56'01; // 'WBV\1'

namespace winrt::WinUI3Package::implementation
{
	LRESULT CALLBACK WebView::hostSubclassProc(
		HWND hwnd, 
		UINT msg, 
		WPARAM wParam, 
		LPARAM lParam,
		UINT_PTR /*id*/, 
		DWORD_PTR ref)
	{
		if (msg == WM_NCLBUTTONUP)
		{
			UINT command = 0;
			switch (wParam)
			{
				case HTCLOSE:     command = SC_CLOSE; break;
				case HTMINBUTTON: command = SC_MINIMIZE; break;
				case HTMAXBUTTON: command = ::IsZoomed(hwnd) ? SC_RESTORE : SC_MAXIMIZE; break;
				default:          break;
			}
			if (command)
			{
				if (command == SC_CLOSE)
				{
					if (auto* self = reinterpret_cast<WebView*>(ref))
						self->m_mouseHook.reset();
				}

				::PostMessageW(hwnd, WM_SYSCOMMAND, command, lParam);
				return 0; // handled: skip DefWindowProc so the command is not raised twice
			}
		}

		return ::DefSubclassProc(hwnd, msg, wParam, lParam);
	}

	constexpr static auto operator*(winrt::Windows::Foundation::Rect rect, float scale)
	{
		return winrt::Windows::Foundation::Rect
		{
			rect.X * scale,
			rect.Y * scale,
			rect.Width * scale,
			rect.Height * scale
		};
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::s_canGoBackProperty{ nullptr };
	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::s_canGoForwardProperty{ nullptr };
	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::s_containsFullScreenElementProperty{ nullptr };
	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::s_defaultBackgroundColorProperty{ nullptr };
	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::s_documentTitleProperty{ nullptr };
	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::s_sourceProperty{ nullptr };

	void WebView::EnsureDependencyProperties()
	{
		if (s_canGoBackProperty)
			return;

		s_canGoBackProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CanGoBack",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
		);

		s_canGoForwardProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"CanGoForward",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
		);

		s_containsFullScreenElementProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"ContainsFullScreenElement",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false) }
		);

		s_defaultBackgroundColorProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"DefaultBackgroundColor",
			winrt::xaml_typename<winrt::Windows::UI::Color>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &WebView::onDefaultBackgroundColorChanged }
		);

		s_documentTitleProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"DocumentTitle",
			winrt::xaml_typename<winrt::hstring>(),
			winrt::xaml_typename<class_type>(),
			nullptr
		);

		s_sourceProperty = winrt::Microsoft::UI::Xaml::DependencyProperty::Register(
			L"Source",
			winrt::xaml_typename<winrt::Windows::Foundation::Uri>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ nullptr, &WebView::onSourceChanged }
		);
	}

	WebView::WebView()
	{
		IsTabStop(true);
		Loaded({ this, &WebView::onLoaded });
		GotFocus([this](auto&&...)
		{
			if (m_webview)
				m_webview.MoveFocus(winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusReason::Programmatic);
		});
		Unloaded([this](auto&&...)
		{
			Close();
			m_mouseHook.reset();
			m_hostHwnd = nullptr;
			::ResetEvent(m_loaded.get());
		});
		LayoutUpdated([this](auto&&...) 
		{
			if (!m_webview)
				return;

			auto const scale = XamlRoot().RasterizationScale();
			auto const newBounds = getBounds(scale);
			if (newBounds == m_cachedBounds)
				return;

			m_cachedBounds = newBounds;
			m_webview.Bounds(m_cachedBounds);
		});
	}

	bool WebView::CanGoBack()
	{
		return winrt::unbox_value<bool>(GetValue(s_canGoBackProperty));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::CanGoBackProperty()
	{
		return s_canGoBackProperty;
	}

	bool WebView::CanGoForward()
	{
		return winrt::unbox_value<bool>(GetValue(s_canGoForwardProperty));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::CanGoForwardProperty()
	{
		return s_canGoForwardProperty;
	}

	bool WebView::ContainsFullScreenElement()
	{
		return winrt::unbox_value<bool>(GetValue(s_containsFullScreenElementProperty));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::ContainsFullScreenElementProperty()
	{
		return s_containsFullScreenElementProperty;
	}

	winrt::Windows::UI::Color WebView::DefaultBackgroundColor()
	{
		return winrt::unbox_value<winrt::Windows::UI::Color>(GetValue(s_defaultBackgroundColorProperty));
	}

	void WebView::DefaultBackgroundColor(winrt::Windows::UI::Color value)
	{
		SetValue(s_defaultBackgroundColorProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::DefaultBackgroundColorProperty()
	{
		return s_defaultBackgroundColorProperty;
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Controls::WebViewDeferredPermissionRequest> WebView::DeferredPermissionRequests()
	{
		return winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Controls::WebViewDeferredPermissionRequest>();
	}

	winrt::hstring WebView::DocumentTitle()
	{
		return winrt::unbox_value<winrt::hstring>(GetValue(s_documentTitleProperty));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::DocumentTitleProperty()
	{
		return s_documentTitleProperty;
	}

	winrt::Windows::Web::UI::WebViewControlSettings WebView::Settings()
	{
		return m_webview ? m_webview.Settings() : nullptr;
	}

	winrt::Windows::Foundation::Uri WebView::Source()
	{
		return GetValue(s_sourceProperty).as<winrt::Windows::Foundation::Uri>();
	}

	void WebView::Source(winrt::Windows::Foundation::Uri const& value)
	{
		SetValue(s_sourceProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty WebView::SourceProperty()
	{
		return s_sourceProperty;
	}

#pragma region Events
	winrt::event_token WebView::ContentLoading(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlContentLoadingEventArgs> const& handler)
	{
		return m_contentLoading.add(handler);
	}

	void WebView::ContentLoading(winrt::event_token const& token)
	{
		m_contentLoading.remove(token);
	}

	winrt::event_token WebView::DOMContentLoaded(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlDOMContentLoadedEventArgs> const& handler)
	{
		return m_domContentLoaded.add(handler);
	}

	void WebView::DOMContentLoaded(winrt::event_token const& token)
	{
		m_domContentLoaded.remove(token);
	}

	winrt::event_token WebView::FrameContentLoading(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlContentLoadingEventArgs> const& handler)
	{
		return m_frameContentLoading.add(handler);
	}

	void WebView::FrameContentLoading(winrt::event_token const& token)
	{
		m_frameContentLoading.remove(token);
	}

	winrt::event_token WebView::FrameDOMContentLoaded(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlDOMContentLoadedEventArgs> const& handler)
	{
		return m_frameDOMContentLoaded.add(handler);
	}

	void WebView::FrameDOMContentLoaded(winrt::event_token const& token)
	{
		m_frameDOMContentLoaded.remove(token);
	}

	winrt::event_token WebView::FrameNavigationStarting(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationStartingEventArgs> const& handler)
	{
		return m_frameNavigationStarting.add(handler);
	}

	void WebView::FrameNavigationStarting(winrt::event_token const& token)
	{
		m_frameNavigationStarting.remove(token);
	}

	winrt::event_token WebView::MoveFocusRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusRequestedEventArgs> const& handler)
	{
		return m_moveFocusRequested.add(handler);
	}

	void WebView::MoveFocusRequested(winrt::event_token const& token)
	{
		m_moveFocusRequested.remove(token);
	}

	winrt::event_token WebView::LongRunningScriptDetected(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlLongRunningScriptDetectedEventArgs> const& handler)
	{
		return m_longRunningScriptDetected.add(handler);
	}

	void WebView::LongRunningScriptDetected(winrt::event_token const& token)
	{
		m_longRunningScriptDetected.remove(token);
	}

	winrt::event_token WebView::NavigationStarting(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationStartingEventArgs> const& handler)
	{
		return m_navigationStarting.add(handler);
	}

	void WebView::NavigationStarting(winrt::event_token const& token)
	{
		m_navigationStarting.remove(token);
	}

	winrt::event_token WebView::NavigationCompleted(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNavigationCompletedEventArgs> const& handler)
	{
		return m_navigationCompleted.add(handler);
	}

	void WebView::NavigationCompleted(winrt::event_token const& token)
	{
		m_navigationCompleted.remove(token);
	}

	winrt::event_token WebView::NewWindowRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlNewWindowRequestedEventArgs> const& handler)
	{
		return m_newWindowRequested.add(handler);
	}

	void WebView::NewWindowRequested(winrt::event_token const& token)
	{
		m_newWindowRequested.remove(token);
	}

	winrt::event_token WebView::PermissionRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlPermissionRequestedEventArgs> const& handler)
	{
		return m_permissionRequested.add(handler);
	}

	void WebView::PermissionRequested(winrt::event_token const& token)
	{
		m_permissionRequested.remove(token);
	}

	winrt::event_token WebView::ScriptNotify(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlScriptNotifyEventArgs> const& handler)
	{
		return m_scriptNotify.add(handler);
	}

	void WebView::ScriptNotify(winrt::event_token const& token)
	{
		m_scriptNotify.remove(token);
	}

	winrt::event_token WebView::UnsafeContentWarningDisplaying(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Foundation::IInspectable> const& handler)
	{
		return m_unsafeContentWarningDisplaying.add(handler);
	}

	void WebView::UnsafeContentWarningDisplaying(winrt::event_token const& token)
	{
		m_unsafeContentWarningDisplaying.remove(token);
	}

	winrt::event_token WebView::UnsupportedUriSchemeIdentified(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlUnsupportedUriSchemeIdentifiedEventArgs> const& handler)
	{
		return m_unsupportedUriSchemeIdentified.add(handler);
	}

	void WebView::UnsupportedUriSchemeIdentified(winrt::event_token const& token)
	{
		m_unsupportedUriSchemeIdentified.remove(token);
	}

	winrt::event_token WebView::UnviewableContentIdentified(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlUnviewableContentIdentifiedEventArgs> const& handler)
	{
		return m_unviewableContentIdentified.add(handler);
	}

	void WebView::UnviewableContentIdentified(winrt::event_token const& token)
	{
		m_unviewableContentIdentified.remove(token);
	}

	winrt::event_token WebView::WebResourceRequested(winrt::Windows::Foundation::TypedEventHandler<winrt::WinUI3Package::WebView, winrt::Windows::Web::UI::WebViewControlWebResourceRequestedEventArgs> const& handler)
	{
		return m_webResourceRequested.add(handler);
	}

	void WebView::WebResourceRequested(winrt::event_token const& token)
	{
		m_webResourceRequested.remove(token);
	}
#pragma endregion

#pragma region Methods
	void WebView::AddInitializeScript(winrt::hstring const& script)
	{
		if (m_webview)
			m_webview.AddInitializeScript(script);
	}
	winrt::Windows::Foundation::Uri WebView::BuildLocalStreamUri(winrt::hstring const& contentIdentifier, winrt::hstring const& relativePath)
	{
		if (m_webview)
			return m_webview.BuildLocalStreamUri(contentIdentifier, relativePath);
		return nullptr;
	}
	winrt::Windows::Foundation::IAsyncAction WebView::CapturePreviewToStreamAsync(winrt::Windows::Storage::Streams::IRandomAccessStream stream)
	{
		auto lifetime = get_strong();
		co_await waitForLoadAsync();
		co_await m_webview.CapturePreviewToStreamAsync(stream);
	}
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::ApplicationModel::DataTransfer::DataPackage> WebView::CaptureSelectedContentToDataPackageAsync()
	{
		auto lifetime = get_strong();
		co_await waitForLoadAsync();
		co_return co_await m_webview.CaptureSelectedContentToDataPackageAsync();
	}
	void WebView::Close()
	{
		if (m_hostHwnd)
			::RemoveWindowSubclass(m_hostHwnd, &WebView::hostSubclassProc, kHostSubclassId);

		if (auto webview = std::exchange(m_webview, nullptr))
			webview.Close();
	}
	void WebView::GetDeferredPermissionRequestById(uint32_t id, winrt::Windows::Web::UI::WebViewControlDeferredPermissionRequest& request)
	{
		if (m_webview)
			m_webview.GetDeferredPermissionRequestById(id, request);
	}
	void WebView::GoBack()
	{
		if (m_webview)
			m_webview.GoBack();
	}
	void WebView::GoForward()
	{
		if (m_webview)
			m_webview.GoForward();
	}
	winrt::Windows::Foundation::IAsyncOperation<winrt::hstring> WebView::InvokeScriptAsync(winrt::hstring scriptName, winrt::Windows::Foundation::Collections::IIterable<winrt::hstring> arguments)
	{
		auto lifetime = get_strong();
		co_await waitForLoadAsync();
		co_return co_await m_webview.InvokeScriptAsync(scriptName, arguments);
	}
	void WebView::MoveFocus(winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusReason const& reason)
	{
		if (m_webview)
			m_webview.MoveFocus(reason);
	}
	void WebView::Navigate(winrt::Windows::Foundation::Uri const& source)
	{
		if (m_webview)
			m_webview.Navigate(source);
	}
	void WebView::NavigateToLocalStreamUri(winrt::Windows::Foundation::Uri const& source, winrt::Windows::Web::IUriToStreamResolver const& streamResolver)
	{
		if (m_webview)
			m_webview.NavigateToLocalStreamUri(source, streamResolver);
	}
	void WebView::NavigateToString(winrt::hstring const& text)
	{
		if (m_webview)
			m_webview.NavigateToString(text);
	}
	void WebView::NavigateWithHttpRequestMessage(winrt::Windows::Web::Http::HttpRequestMessage const& requestMessage)
	{
		if (m_webview)
			m_webview.NavigateWithHttpRequestMessage(requestMessage);
	}
	void WebView::Refresh()
	{
		if (m_webview)
			m_webview.Refresh();
	}
	void WebView::Stop()
	{
		if (m_webview)
			m_webview.Stop();
	}
	WebView::~WebView()
	{
		m_mouseHook.reset();
	}
#pragma endregion

	winrt::fire_and_forget WebView::onLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
	{
		auto strongThis = get_strong();
		auto xamlRoot = XamlRoot();
		auto const hwnd = GetHwnd(xamlRoot);

		m_webview = co_await m_process.CreateWebViewControlAsync(reinterpret_cast<int64_t>(hwnd), getBounds(xamlRoot.RasterizationScale()));
		
		m_webview.MoveFocusRequested(
			[this](auto const&, winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusRequestedEventArgs const& args)
			{
				auto const direction = args.Reason() == winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusReason::Previous
					? winrt::Microsoft::UI::Xaml::Input::FocusNavigationDirection::Previous
					: winrt::Microsoft::UI::Xaml::Input::FocusNavigationDirection::Next;
				winrt::Microsoft::UI::Xaml::Input::FocusManager::TryMoveFocus(direction);
				m_moveFocusRequested(*this, args);
			});

		m_webview.ContentLoading([this](auto const&, auto const& args) { m_contentLoading(*this, args); });
		m_webview.DOMContentLoaded([this](auto const&, auto const& args) { m_domContentLoaded(*this, args); });
		m_webview.FrameContentLoading([this](auto const&, auto const& args) { m_frameContentLoading(*this, args); });
		m_webview.FrameDOMContentLoaded([this](auto const&, auto const& args) { m_frameDOMContentLoaded(*this, args); });
		m_webview.FrameNavigationStarting([this](auto const&, auto const& args) { m_frameNavigationStarting(*this, args); });
		m_webview.LongRunningScriptDetected([this](auto const&, auto const& args) { m_longRunningScriptDetected(*this, args); });
		m_webview.NavigationStarting([this](auto const&, auto const& args) { m_navigationStarting(*this, args); });
		m_webview.NavigationCompleted([this](auto const&, auto const& args)
		{
			SetValue(s_canGoBackProperty, winrt::box_value(m_webview.CanGoBack()));
			SetValue(s_canGoForwardProperty, winrt::box_value(m_webview.CanGoForward()));
			SetValue(s_documentTitleProperty, winrt::box_value(m_webview.DocumentTitle()));
			m_navigationCompleted(*this, args);
		});
		m_webview.ContainsFullScreenElementChanged([this](auto const&, auto const&)
		{
			SetValue(s_containsFullScreenElementProperty, winrt::box_value(m_webview.ContainsFullScreenElement()));
		});
		m_webview.NewWindowRequested([this](auto const&, auto const& args) { m_newWindowRequested(*this, args); });
		m_webview.PermissionRequested([this](auto const&, auto const& args) { m_permissionRequested(*this, args); });
		m_webview.ScriptNotify([this](auto const&, auto const& args) { m_scriptNotify(*this, args); });
		m_webview.UnsafeContentWarningDisplaying([this](auto const&, auto const& args) { m_unsafeContentWarningDisplaying(*this, args); });
		m_webview.UnsupportedUriSchemeIdentified([this](auto const&, auto const& args) { m_unsupportedUriSchemeIdentified(*this, args); });
		m_webview.UnviewableContentIdentified([this](auto const&, auto const& args) { m_unviewableContentIdentified(*this, args); });
		m_webview.WebResourceRequested([this](auto const&, auto const& args) { m_webResourceRequested(*this, args); });

		setProperties();

		// Intercept right-clicks that land inside the webview so the window-level context
		// menu is never raised. See WebViewMouseHook.
		m_hostHwnd = hwnd;
		m_mouseHook.emplace(this);

		// Subclass the top-level window so a click on the caption buttons is not eaten
		// on the first click (with a beep) while the out-of-process web content holds
		// focus. Removed in Close().
		if (m_hostHwnd)
		{
			::SetWindowSubclass(
				m_hostHwnd, 
				&WebView::hostSubclassProc, 
				kHostSubclassId,
				reinterpret_cast<DWORD_PTR>(this)
			);
		}

		// Release any callers parked in waitForLoadAsync().
		::SetEvent(m_loaded.get());
	}

	bool WebView::isPointInWebView(POINT screenPoint) const
	{
		// m_cachedBounds is the webview's rectangle in the host window's client area
		// (physical pixels), kept up to date by LayoutUpdated.
		if (!m_hostHwnd || m_cachedBounds.Width <= 0 || m_cachedBounds.Height <= 0)
			return false;

		POINT topLeft{ static_cast<LONG>(m_cachedBounds.X), static_cast<LONG>(m_cachedBounds.Y) };
		if (!::ClientToScreen(m_hostHwnd, &topLeft))
			return false;

		RECT const rect{
			topLeft.x,
			topLeft.y,
			topLeft.x + static_cast<LONG>(m_cachedBounds.Width),
			topLeft.y + static_cast<LONG>(m_cachedBounds.Height)
		};
		return ::PtInRect(&rect, screenPoint);
	}

	winrt::Windows::Foundation::IAsyncAction WebView::waitForLoadAsync()
	{
		if (m_webview)
			co_return;

		// Capture the dispatcher on the UI thread before suspending.
		auto dispatcher = DispatcherQueue();
		co_await winrt::resume_on_signal(m_loaded.get());
		co_await wil::resume_foreground(dispatcher);
	}

	void WebView::setProperties()
	{
		auto unsetValue = winrt::Microsoft::UI::Xaml::DependencyProperty::UnsetValue();

		if (auto const defaultBackgroundColorValue = ReadLocalValue(s_defaultBackgroundColorProperty); defaultBackgroundColorValue != unsetValue)
			m_webview.DefaultBackgroundColor(winrt::unbox_value<winrt::Windows::UI::Color>(defaultBackgroundColorValue));

		if (auto const sourceValue = ReadLocalValue(s_sourceProperty); sourceValue != unsetValue)
			m_webview.Source(sourceValue.as<winrt::Windows::Foundation::Uri>());
	}

	winrt::Windows::Foundation::Rect WebView::getBounds(double scale)
	{
		return TransformToVisual(nullptr).TransformBounds(winrt::Windows::Foundation::Rect{
			0, 0,
			static_cast<float>(ActualWidth()),
			static_cast<float>(ActualHeight())
		}) * scale;
	}

	void WebView::onDefaultBackgroundColorChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		if (self->m_webview)
			self->m_webview.DefaultBackgroundColor(winrt::unbox_value<winrt::Windows::UI::Color>(e.NewValue()));
	}

	void WebView::onSourceChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e)
	{
		auto self = GetSelf(d);
		if (self->m_webview)
			self->m_webview.Source(e.NewValue().as<winrt::Windows::Foundation::Uri>());
	}
}
