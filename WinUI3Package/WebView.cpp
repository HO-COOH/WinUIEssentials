#include "pch.h"
#include "WebView.h"
#if __has_include("WebView.g.cpp")
#include "WebView.g.cpp"
#endif
#include <include/HwndHelper.hpp>

namespace winrt::WinUI3Package::implementation
{
	constexpr auto operator*(winrt::Windows::Foundation::Rect rect, float scale)
	{
		return winrt::Windows::Foundation::Rect
		{
			rect.X * scale,
			rect.Y * scale,
			rect.Width * scale,
			rect.Height * scale
		};
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
			if (m_webview)
			{
				m_webview.Close();
				m_webview = nullptr;
			}
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

	bool WebView::CanGoForward()
	{
		return false;
	}

	bool WebView::ContainsFullScreenElement()
	{
		return false;
	}

	winrt::Windows::UI::Color WebView::DefaultBackgroundColor()
	{
		return winrt::Windows::UI::Color();
	}

	void WebView::DefaultBackgroundColor(winrt::Windows::UI::Color value)
	{
	}

	winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Controls::WebViewDeferredPermissionRequest> WebView::DeferredPermissionRequests()
	{
		return winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Controls::WebViewDeferredPermissionRequest>();
	}

	winrt::hstring WebView::DocumentTitle()
	{
		return winrt::hstring();
	}

	winrt::Windows::UI::Xaml::Controls::WebViewSettings WebView::Settings()
	{
		return winrt::Windows::UI::Xaml::Controls::WebViewSettings();
	}

	winrt::Windows::Foundation::Uri WebView::Source()
	{
		return winrt::Windows::Foundation::Uri();
	}

	void WebView::Source(winrt::Windows::Foundation::Uri const& value)
	{
	}

	winrt::fire_and_forget WebView::onLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
	{
		auto strongThis = get_strong();
		auto xamlRoot = XamlRoot();
		auto const hwnd = GetHwnd(xamlRoot);

		m_webview = co_await m_process.CreateWebViewControlAsync(reinterpret_cast<int64_t>(hwnd), getBounds(xamlRoot.RasterizationScale()));
		m_webview.Source(winrt::Windows::Foundation::Uri{ L"https://www.google.com" });

		m_webview.MoveFocusRequested(
			[](auto const&, winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusRequestedEventArgs const& args)
			{
				auto const direction = args.Reason() == winrt::Windows::Web::UI::Interop::WebViewControlMoveFocusReason::Previous
					? winrt::Microsoft::UI::Xaml::Input::FocusNavigationDirection::Previous
					: winrt::Microsoft::UI::Xaml::Input::FocusNavigationDirection::Next;
				winrt::Microsoft::UI::Xaml::Input::FocusManager::TryMoveFocus(direction);
			});
	}

	winrt::Windows::Foundation::Rect WebView::getBounds(double scale)
	{
		return TransformToVisual(nullptr).TransformBounds(winrt::Windows::Foundation::Rect{
			0, 0,
			static_cast<float>(ActualWidth()),
			static_cast<float>(ActualHeight())
		}) * scale;
	}
}
