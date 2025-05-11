#include "pch.h"
#include "MorphAnimationHelper.h"

namespace MorphAnimationHelper
{
	winrt::Microsoft::UI::Composition::CompositionAnimation CreateSourceScaleAnimation(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		winrt::Windows::Foundation::Numerics::float2 sourceSize,
		winrt::Windows::Foundation::Numerics::float2 targetSize,
		bool isSourceToTarget,
		std::chrono::milliseconds duration)
	{
		auto scaleAnimation = compositor.CreateVector3KeyFrameAnimation();
		scaleAnimation.Target(L"Scale");
		if (duration != std::chrono::milliseconds{})
			scaleAnimation.Duration(duration);
		if (isSourceToTarget)
		{
			scaleAnimation.InsertKeyFrame(1.f, { targetSize / sourceSize, 1.f });
		}
		else
		{
			scaleAnimation.InsertKeyFrame(0.f, { sourceSize / targetSize, 1.f });
			scaleAnimation.InsertKeyFrame(1.f, { 1.f, 1.f, 1.f });
		}
		return scaleAnimation;
	}

	 winrt::Microsoft::UI::Composition::CompositionAnimation CreateTranslationAnimation(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		winrt::Windows::Foundation::Point p,
		bool isSourceToTarget,
		std::chrono::milliseconds duration
	)
	{
		auto translationAnimation = compositor.CreateVector2KeyFrameAnimation();
		translationAnimation.Target(L"Translation.XY");
		if (duration != std::chrono::milliseconds{})
			translationAnimation.Duration(duration);
		if (isSourceToTarget)
		{
			translationAnimation.InsertKeyFrame(1.f, { -p.X, -p.Y });
		}
		else
		{
			translationAnimation.InsertKeyFrame(0.f, { p.X, p.Y });
			translationAnimation.InsertKeyFrame(1.f, {});
		}
		return translationAnimation;
	}

	 winrt::Microsoft::UI::Composition::CompositionAnimation CreateOpacityAnimation(
		winrt::Microsoft::UI::Composition::Compositor const& compositor,
		bool isSourceToTarget,
		std::chrono::milliseconds duration
	)
	{
		auto opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
		opacityAnimation.Target(L"Opacity");
		if (duration != std::chrono::milliseconds{})
			opacityAnimation.Duration(duration);
		if (isSourceToTarget)
			opacityAnimation.InsertKeyFrame(1.f, 0.f);
		else
		{
			opacityAnimation.InsertKeyFrame(0.f, 0.f);
			opacityAnimation.InsertKeyFrame(1.f, 1.f);
		}
		return opacityAnimation;
	}
}
