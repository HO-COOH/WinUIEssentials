#pragma once
#include <winrt/Windows.Foundation.h>
#include <chrono>
#include "AnimatedValue.hpp"
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

class AnimatedToolTipPlacement
{
	std::chrono::steady_clock::time_point m_animationStartTime;
	AnimatedValue<float> m_widthValue;
	AnimatedValue<winrt::Windows::Foundation::Point> m_positionValue;
	winrt::Windows::Foundation::Point m_anchor{};
	winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer m_animationTimer{ nullptr };
	winrt::Microsoft::UI::Dispatching::DispatcherQueueTimer::Tick_revoker m_animationRevoker;

	constexpr static std::chrono::milliseconds PlacementAnimationDuration{ 250 };
	void updatePlacementRect(winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip);
public:
	float CurrentWidth{};
	winrt::Windows::Foundation::Point CurrentPosition{};

	//anchor is where the caller has moved the PlacementTarget's top-left corner to, PlacementRect is relative to it
	void StartAnimation(
		winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip,
		float widthFrom,
		float widthTo,
		winrt::Windows::Foundation::Point positionFrom,
		winrt::Windows::Foundation::Point positionTo,
		winrt::Windows::Foundation::Point anchor
	);
	void StopAnimation();
	void OnRendering(winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip);

	[[nodiscard]] bool IsAnimating() const;
};