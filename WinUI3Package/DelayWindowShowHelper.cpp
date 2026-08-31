#include "pch.h"
#include "DelayWindowShowHelper.h"

void DelayWindowShowHelper::onRendering(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Media::RenderedEventArgs const& arg)
{
	if (++m_renderedCount > 2)
		showWindow();
}

void DelayWindowShowHelper::onDispatcherTimerTick(winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer const& timer, winrt::Windows::Foundation::IInspectable const&)
{
	if (++m_tick > 10)
		showWindow();
}

void DelayWindowShowHelper::showWindow()
{
	if (std::exchange(m_shown, true))
		return;

	m_allowShow = true;
	m_renderingRevoker.revoke();
	m_dispatcherTimer.Stop();
	m_dispatcherRevoker.revoke();
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
}

DelayWindowShowHelper::DelayWindowShowHelper(HWND hwnd, winrt::Microsoft::UI::Dispatching::DispatcherQueue const& queue) : 
	m_dispatcherTimer{queue.CreateTimer() }, 
	m_hwnd{hwnd}
{
	m_dispatcherTimer.Interval(std::chrono::milliseconds{ 100 });
	m_dispatcherRevoker = m_dispatcherTimer.Tick(winrt::auto_revoke, { this, &DelayWindowShowHelper::onDispatcherTimerTick });
	m_dispatcherTimer.Start();
}

void DelayWindowShowHelper::OnWM_WindowPosChanging(WINDOWPOS& windowPos)
{
	if(!m_allowShow)
		windowPos.flags &= ~SWP_SHOWWINDOW;
}
