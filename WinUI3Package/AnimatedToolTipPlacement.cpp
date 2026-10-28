#include "pch.h"
#include "AnimatedToolTipPlacement.h"
#include "Easing.hpp"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

//DispatcherQueueTimer is not tied to the display, so ask DWM how long one refresh is
static winrt::Windows::Foundation::TimeSpan refreshInterval()
{
	DWM_TIMING_INFO timing{ .cbSize = sizeof(DWM_TIMING_INFO) };
	if (SUCCEEDED(DwmGetCompositionTimingInfo(nullptr, &timing)) && timing.rateRefresh.uiNumerator != 0)
	{
		return std::chrono::duration_cast<winrt::Windows::Foundation::TimeSpan>(
			std::chrono::duration<double>{ static_cast<double>(timing.rateRefresh.uiDenominator) / timing.rateRefresh.uiNumerator });
	}
	return std::chrono::milliseconds{ 16 };
}

void AnimatedToolTipPlacement::OnRendering(winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip)
{
	if (!toolTip.IsOpen())
	{
		StopAnimation();
		toolTip.ClearValue(winrt::Microsoft::UI::Xaml::FrameworkElement::WidthProperty());
		return;
	}

	auto const elapsed = std::chrono::steady_clock::now() - m_animationStartTime;
	auto const progress = (std::min)(std::chrono::duration<double>{ elapsed } / PlacementAnimationDuration, 1.0);
	auto const easedProgress = EasedProgress(progress, 3);

	toolTip.Width(CurrentWidth = m_widthValue.Lerp(easedProgress));
	toolTip.UpdateLayout();
	CurrentPosition = m_positionValue.Lerp(easedProgress);
	updatePlacementRect(toolTip);

	if (easedProgress >= 1.f)
	{
		StopAnimation();
		toolTip.ClearValue(winrt::Microsoft::UI::Xaml::FrameworkElement::WidthProperty());
	}
}

void AnimatedToolTipPlacement::StartAnimation(
	winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip,
	float widthFrom,
	float widthTo,
	winrt::Windows::Foundation::Point positionFrom,
	winrt::Windows::Foundation::Point positionTo,
	winrt::Windows::Foundation::Point anchor)
{
	m_animationStartTime = std::chrono::steady_clock::now();

	m_widthValue.m_from = widthFrom;
	m_widthValue.m_to = widthTo;
	toolTip.Width(CurrentWidth = widthFrom);

	m_positionValue.m_from = positionFrom;
	m_positionValue.m_to = positionTo;
	//The target is already at the destination anchor (it still picks the monitor), the animated position is applied through PlacementRect
	m_anchor = anchor;
	CurrentPosition = positionFrom;
	updatePlacementRect(toolTip);

	if (IsAnimating())
		return;

	if (!m_animationTimer)
		m_animationTimer = toolTip.DispatcherQueue().CreateTimer();
	m_animationTimer.Interval(refreshInterval());
	m_animationRevoker = m_animationTimer.Tick(winrt::auto_revoke, [toolTip, this](auto&&...) {
		OnRendering(toolTip);
	});
	m_animationTimer.Start();
}

void AnimatedToolTipPlacement::updatePlacementRect(winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip)
{
	//PlacementRect is relative to the target. Its top stays at the anchor (caption top), Bottom placement attaches the tooltip to its bottom edge
	toolTip.PlacementRect(winrt::Windows::Foundation::Rect{
		CurrentPosition.X - m_anchor.X,
		0.f,
		1.f,
		CurrentPosition.Y - m_anchor.Y
	});
}

void AnimatedToolTipPlacement::StopAnimation()
{
	m_animationRevoker.revoke();
	if (m_animationTimer)
		m_animationTimer.Stop();
}

bool AnimatedToolTipPlacement::IsAnimating() const
{
	return static_cast<bool>(m_animationRevoker);
}
