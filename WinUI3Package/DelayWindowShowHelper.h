#pragma once
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winuser.h>

class DelayWindowShowHelper
{
	void onRendering(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Media::RenderedEventArgs const& arg);
	void onDispatcherTimerTick(winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer const& timer, winrt::Windows::Foundation::IInspectable const&);
	void showWindow();

	bool m_allowShow{};
	bool m_shown{};
	int m_renderedCount{};
	int m_tick{};
	winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendered_revoker m_renderingRevoker = 
		winrt::Microsoft::UI::Xaml::Media::CompositionTarget::Rendered(winrt::auto_revoke, { this, &DelayWindowShowHelper::onRendering });
	winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_dispatcherTimer{ nullptr };
	winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer::Tick_revoker m_dispatcherRevoker;
	HWND m_hwnd;
public:
	DelayWindowShowHelper(HWND hwnd, winrt::Microsoft::UI::Dispatching::DispatcherQueue const& queue);
	void OnWM_WindowPosChanging(WINDOWPOS& windowPos);
};