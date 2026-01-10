#pragma once
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>

class ButtonAnimations
{
	struct BasicAnimation
	{
		winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation translationAnimation{ nullptr };
		winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation opacityAnimation{ nullptr };
	};

	struct AdditionalElementAnimation
	{
		winrt::Microsoft::UI::Composition::ScalarKeyFrameAnimation opacityAnimation{ nullptr };
		winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation translationAnimation{ nullptr };
	};

	struct SourceButtonAnimation : BasicAnimation
	{
		winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation scaleAnimation{ nullptr };
	};

	struct TargetButtonAnimation : BasicAnimation
	{
		winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation clipCornerRadiusAnimation{ nullptr };
		winrt::Microsoft::UI::Composition::ExpressionAnimation clipOffsetExpressionAnimation{ nullptr };
		winrt::Microsoft::UI::Composition::Vector2KeyFrameAnimation clipSizeAnimation{ nullptr };
		AdditionalElementAnimation additionalElementsAnimation;
	};

	winrt::Microsoft::UI::Composition::Visual sourceVisual{ nullptr };
	winrt::Microsoft::UI::Composition::Visual targetVisual{ nullptr };

	SourceButtonAnimation sourceButtonForwardAnimation;
	TargetButtonAnimation targetButtonForwardAnimation;

	winrt::Microsoft::UI::Composition::CompositionRoundedRectangleGeometry clip{ nullptr };

	winrt::Microsoft::UI::Composition::Compositor compositor{ nullptr };
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::Control> sourceButtonRef;
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::Control> targetButtonRef;

	void makeTranslationAnimations(
		winrt::Windows::Foundation::Numerics::float2 translationVector
	);

	void makeOpacityAnimations();

	void makeScaleAnimations(
		winrt::Windows::Foundation::Numerics::float2 sourceSize,
		winrt::Windows::Foundation::Numerics::float2 targetSize
	);

	void makeClipAnimations(
		winrt::Microsoft::UI::Xaml::CornerRadius sourceCornerRadius,
		winrt::Microsoft::UI::Xaml::CornerRadius targetCornerRadius,
		winrt::Windows::Foundation::Numerics::float2 sourceSize,
		winrt::Windows::Foundation::Numerics::float2 targetSize
	);

	void makeTargetButtonElementAnimations();
public:
	void CreateForwardPass(
		winrt::Microsoft::UI::Xaml::Controls::Control const& sourceButton,
		winrt::Microsoft::UI::Xaml::Controls::Control const& targetButton
	);

	void Play();
};
