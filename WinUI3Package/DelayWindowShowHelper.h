#pragma once
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winuser.h>

class DelayWindowShowHelper
{
	void onRendered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Media::RenderedEventArgs const& arg);
	void onDispatcherTimerTick(winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer const& timer, winrt::Windows::Foundation::IInspectable const&);
	void markReadyToShow();
	void showWindow();

	bool m_readyToShow{};
	bool m_showRequested{};
	bool m_shown{};
	int m_renderedCount{};
	int m_tick{};
	winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_dispatcherTimer{ nullptr };
	winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer::Tick_revoker m_dispatcherRevoker;
	winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendered_revoker m_renderingRevoker =
		winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendered(winrt::auto_revoke, { this, &DelayWindowShowHelper::onRendered });
	HWND m_hwnd;
public:
	DelayWindowShowHelper(HWND hwnd, winrt::Microsoft::UI::Dispatching::DispatcherQueue const& queue);
	void RequestShow();
	void OnWM_WindowPosChanging(WINDOWPOS& windowPos);
};