#include "pch.h"
#include "ButtonAnimations.h"
#include <chrono>

constexpr std::chrono::seconds duration{ 5 };


void ButtonAnimations::makeTranslationAnimations(
	winrt::Windows::Foundation::Numerics::float2 translationVector
)
{
	sourceButtonForwardAnimation.translationAnimation = compositor.CreateVector2KeyFrameAnimation();
	sourceButtonForwardAnimation.translationAnimation.InsertKeyFrame(0.0f, { });
	sourceButtonForwardAnimation.translationAnimation.InsertKeyFrame(1.0f, -translationVector);
	sourceButtonForwardAnimation.translationAnimation.Duration(duration);

	targetButtonForwardAnimation.translationAnimation = compositor.CreateVector2KeyFrameAnimation();
	targetButtonForwardAnimation.translationAnimation.InsertKeyFrame(0.0f, translationVector);
	targetButtonForwardAnimation.translationAnimation.InsertKeyFrame(1.0f, {});
	targetButtonForwardAnimation.translationAnimation.Duration(duration);
}

void ButtonAnimations::makeOpacityAnimations()
{
	sourceButtonForwardAnimation.opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
	sourceButtonForwardAnimation.opacityAnimation.InsertKeyFrame(0.0f, 1.0f);
	sourceButtonForwardAnimation.opacityAnimation.InsertKeyFrame(0.1f, 1.0f);
	sourceButtonForwardAnimation.opacityAnimation.InsertKeyFrame(0.9f, 0.0f);
	sourceButtonForwardAnimation.opacityAnimation.Duration(duration);

	targetButtonForwardAnimation.opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
	targetButtonForwardAnimation.opacityAnimation.InsertKeyFrame(0.0f, 0.0f);
	targetButtonForwardAnimation.opacityAnimation.InsertKeyFrame(0.9f, 1.0f);
	targetButtonForwardAnimation.opacityAnimation.InsertKeyFrame(1.0f, 1.0f);
	targetButtonForwardAnimation.opacityAnimation.Duration(duration);
}

void ButtonAnimations::makeScaleAnimations(
	winrt::Windows::Foundation::Numerics::float2 sourceSize, 
	winrt::Windows::Foundation::Numerics::float2 targetSize)
{
	sourceButtonForwardAnimation.scaleAnimation = compositor.CreateVector2KeyFrameAnimation();
	sourceButtonForwardAnimation.scaleAnimation.InsertKeyFrame(0.0f, { 1.0f, 1.0f });
	sourceButtonForwardAnimation.scaleAnimation.InsertKeyFrame(1.0f, { targetSize / sourceSize });
	sourceButtonForwardAnimation.scaleAnimation.Duration(duration);
}

void ButtonAnimations::makeClipAnimations(
	winrt::Microsoft::UI::Xaml::CornerRadius sourceCornerRadius, 
	winrt::Microsoft::UI::Xaml::CornerRadius targetCornerRadius,
	winrt::Windows::Foundation::Numerics::float2 sourceSize,
	winrt::Windows::Foundation::Numerics::float2 targetSize
)
{
	clip = compositor.CreateRoundedRectangleGeometry();

	targetButtonForwardAnimation.clipCornerRadiusAnimation = compositor.CreateVector2KeyFrameAnimation();
	targetButtonForwardAnimation.clipCornerRadiusAnimation.InsertKeyFrame(0.0f, { static_cast<float>(sourceCornerRadius.TopLeft), static_cast<float>(sourceCornerRadius.TopLeft) });
	targetButtonForwardAnimation.clipCornerRadiusAnimation.InsertKeyFrame(1.0f, { static_cast<float>(targetCornerRadius.TopLeft), static_cast<float>(targetCornerRadius.TopLeft) });
	targetButtonForwardAnimation.clipCornerRadiusAnimation.Duration(duration);

	targetButtonForwardAnimation.clipOffsetExpressionAnimation = compositor.CreateExpressionAnimation(
		L"Vector2((targetSize.X - clip.Size.X) / 2, (targetSize.Y - clip.Size.Y) / 2)");
	targetButtonForwardAnimation.clipOffsetExpressionAnimation.SetVector2Parameter(L"targetSize", targetSize);
	targetButtonForwardAnimation.clipOffsetExpressionAnimation.SetReferenceParameter(L"clip", clip);

	// Create animations
	targetButtonForwardAnimation.clipSizeAnimation = compositor.CreateVector2KeyFrameAnimation();
	targetButtonForwardAnimation.clipSizeAnimation.InsertKeyFrame(0.0f, sourceSize);
	targetButtonForwardAnimation.clipSizeAnimation.InsertKeyFrame(1.0f, targetSize);
	targetButtonForwardAnimation.clipSizeAnimation.Duration(duration);


	clip.CornerRadius({ static_cast<float>(sourceCornerRadius.TopLeft), static_cast<float>(sourceCornerRadius.TopLeft) });
}

void ButtonAnimations::makeTargetButtonElementAnimations()
{
	targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation = compositor.CreateScalarKeyFrameAnimation();
	targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation.InsertKeyFrame(1.f, 1.f);
	targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation.Duration(duration);
	targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation.Target(L"Opacity");

	targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation = compositor.CreateVector2KeyFrameAnimation();
	targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation.InsertKeyFrame(0.f, { 0.f, 200.f });
	targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation.InsertKeyFrame(1.f, {});
	targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation.Duration(duration);
	targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation.Target(L"Offset.XY");

	//auto animationGroup = compositor.CreateAnimationGroup();
	//animationGroup.Add(targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation);
	//animationGroup.Add(targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation);

	std::chrono::milliseconds delay = duration;
	for (auto element : targetButtonRef.get().as<winrt::Microsoft::UI::Xaml::Controls::ContentControl>().Content().as<winrt::Microsoft::UI::Xaml::Controls::Panel>().Children())
	{
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(element, true);
		targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation.DelayTime(delay);
		targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation.DelayTime(delay);
		auto visual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(element);
		visual.StartAnimation(L"Opacity", targetButtonForwardAnimation.additionalElementsAnimation.opacityAnimation);
		visual.StartAnimation(L"Translation.XY", targetButtonForwardAnimation.additionalElementsAnimation.translationAnimation);
		delay += std::chrono::milliseconds{ 2000 };
	}
}

void ButtonAnimations::CreateForwardPass(
	winrt::Microsoft::UI::Xaml::Controls::Control const& sourceButton,
	winrt::Microsoft::UI::Xaml::Controls::Control const& targetButton)
{
	if (sourceButtonForwardAnimation.opacityAnimation)
		return;

	sourceButtonRef = winrt::make_weak(sourceButton);
	targetButtonRef = winrt::make_weak(targetButton);
	winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(sourceButton, true);
	winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetIsTranslationEnabled(targetButton, true);

	sourceVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(sourceButton);
	targetVisual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(targetButton);
	compositor = sourceVisual.Compositor();

	auto const sourceSize = sourceButton.ActualSize();
	auto const targetSize = targetButton.ActualSize();
	sourceVisual.CenterPoint({ sourceSize.x / 2.f, sourceSize.y / 2.f, 0.f });
	targetVisual.CenterPoint({ targetSize.x / 2.f, targetSize.y / 2.f, 0.f });
	
	winrt::Windows::Foundation::Numerics::float2 sourceCenter = sourceButton.TransformToVisual(nullptr).TransformPoint({ sourceSize.x / 2.f, sourceSize.y / 2.f });
	winrt::Windows::Foundation::Numerics::float2 targetCenter = targetButton.TransformToVisual(nullptr).TransformPoint({ targetSize.x / 2.f, targetSize.y / 2.f });
	auto const translationVector = sourceCenter - targetCenter;
	makeTranslationAnimations(translationVector);

	makeOpacityAnimations();

	makeScaleAnimations(sourceSize, targetSize);

	makeClipAnimations(sourceButton.CornerRadius(), targetButton.CornerRadius(), sourceSize, targetSize);
	targetVisual.Clip(compositor.CreateGeometricClip(clip));
	clip.Size({ sourceSize.x, sourceSize.y });
	makeTargetButtonElementAnimations();
}

void ButtonAnimations::Play()
{
	auto batch = compositor.CreateScopedBatch(winrt::Microsoft::UI::Composition::CompositionBatchTypes::Animation);

	sourceVisual.StartAnimation(L"Translation.XY", sourceButtonForwardAnimation.translationAnimation);
	sourceVisual.StartAnimation(L"Scale.XY", sourceButtonForwardAnimation.scaleAnimation);
	sourceVisual.StartAnimation(L"Opacity", sourceButtonForwardAnimation.opacityAnimation);
	targetVisual.StartAnimation(L"Translation.XY", targetButtonForwardAnimation.translationAnimation);
	targetVisual.StartAnimation(L"Opacity", targetButtonForwardAnimation.opacityAnimation);
	clip.StartAnimation(L"Offset", targetButtonForwardAnimation.clipOffsetExpressionAnimation);
	clip.StartAnimation(L"Size", targetButtonForwardAnimation.clipSizeAnimation);
	clip.StartAnimation(L"CornerRadius", targetButtonForwardAnimation.clipCornerRadiusAnimation);

	batch.End();
	batch.Completed([this](auto&&...) {
		if (auto sourceButton = sourceButtonRef.get())
		{
			auto target = targetButtonRef.get();
			target.IsHitTestVisible(true);
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(sourceButton, L"Normal", false);
			winrt::Microsoft::UI::Xaml::VisualStateManager::GoToState(target, L"Normal", false);
		}
	});

}


