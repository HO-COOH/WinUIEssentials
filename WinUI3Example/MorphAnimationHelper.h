#pragma once
#include <winrt/Microsoft.UI.Composition.h>
#include <chrono>
#include <winrt/Windows.Foundation.Numerics.h>

namespace MorphAnimationHelper
{
	[[nodiscard]] winrt::Microsoft::UI::Composition::CompositionAnimation CreateSourceScaleAnimation(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		winrt::Windows::Foundation::Numerics::float2 sourceSize,
		winrt::Windows::Foundation::Numerics::float2 targetSize,
		bool isSourceToTarget = true,
		std::chrono::milliseconds duration = {});

	[[nodiscard]] winrt::Microsoft::UI::Composition::CompositionAnimation CreateTranslationAnimation(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		winrt::Windows::Foundation::Point p,
		bool isSourceToTarget = true,
		std::chrono::milliseconds duration = {}
	);

	[[nodiscard]] winrt::Microsoft::UI::Composition::CompositionAnimation CreateOpacityAnimation(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		bool isSourceToTarget = true,
		std::chrono::milliseconds duration = {});

	[[nodiscard]] winrt::Microsoft::UI::Composition::CompositionAnimationGroup CreateAnimationGroup(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		auto&&... animations
	)
	{
		auto animationGroup = compositor.CreateAnimationGroup();
		(animationGroup.Add(animations), ...);
		return animationGroup;
	}
}
