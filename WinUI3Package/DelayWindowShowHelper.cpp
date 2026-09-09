#include "pch.h"
#include "DelayWindowShowHelper.h"

void DelayWindowShowHelper::onRendered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Media::RenderedEventArgs const& arg)
{
	if (++m_renderedCount > 1)
		markReadyToShow();
}

void DelayWindowShowHelper::onDispatcherTimerTick(winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer const& timer, winrt::Windows::Foundation::IInspectable const&)
{
	if (++m_tick > 10)
		markReadyToShow();
}

void DelayWindowShowHelper::markReadyToShow()
{
	if (std::exchange(m_readyToShow, true))
		return;


	if (m_showRequested)
		showWindow();

	//Nothing left to wait for, so stop watching frames and ticks
	m_renderingRevoker.revoke();
	m_dispatcherTimer.Stop();
	m_dispatcherRevoker.revoke();
}

void DelayWindowShowHelper::showWindow()
{
	if (std::exchange(m_shown, true))
		return;

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

void DelayWindowShowHelper::RequestShow()
{
	if (std::exchange(m_showRequested, true))
		return;

	//Already rendered while offscreen, so there is nothing left to hide it for
	if (m_readyToShow)
		showWindow();
}

void DelayWindowShowHelper::OnWM_WindowPosChanging(WINDOWPOS& windowPos)
{
	if(m_showRequested && !m_shown)
		windowPos.flags &= ~SWP_SHOWWINDOW;
}
