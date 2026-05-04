#include "pch.h"
#include "Shimmer.AnimationMember.h"


void ShimmerAnimationMember::appendGradientStop(winrt::Windows::UI::Color color, float offset)
{
	appendGradientStop(m_compositor.CreateColorGradientStop(offset, color));
}

void ShimmerAnimationMember::appendGradientStop(
	winrt::WinUINamespace::UI::Composition::CompositionColorGradientStop const& gradientStop)
{
	m_shimmerMaskGradient.ColorStops().Append(gradientStop);
}

ShimmerAnimationMember::ShimmerAnimationMember(
	winrt::WinUINamespace::UI::Composition::Compositor const& compositor,
	winrt::Windows::Foundation::TimeSpan duration) :
	m_gradientStartPointAnimation{ compositor.CreateVector2KeyFrameAnimation() },
	m_gradientStopPointAnimation{ compositor.CreateVector2KeyFrameAnimation() },
	m_rectangleGeometry{ compositor.CreateRoundedRectangleGeometry() },
	m_shimmerMaskGradient{ compositor.CreateLinearGradientBrush() },
	m_compositor{ compositor }
	//m_duration{duration}
{
	m_gradientStartPointAnimation.Duration(duration);
	m_gradientStartPointAnimation.IterationBehavior(winrt::WinUINamespace::UI::Composition::AnimationIterationBehavior::Forever);
	m_gradientStartPointAnimation.InsertKeyFrame(0.0f, { InitialStartPointX, 0.0f });
	m_gradientStartPointAnimation.InsertKeyFrame(1.0f, {});

	m_gradientStopPointAnimation.Duration(duration);
	m_gradientStopPointAnimation.IterationBehavior(winrt::WinUINamespace::UI::Composition::AnimationIterationBehavior::Forever);
	m_gradientStopPointAnimation.InsertKeyFrame(0.0f, { 1.0f, 0.0f });
	m_gradientStopPointAnimation.InsertKeyFrame(1.0f, { -InitialStartPointX, 1.0f });
}

void ShimmerAnimationMember::SetGradientStops(winrt::WinUINamespace::UI::Xaml::Media::GradientStopCollection gradientStops)
{
	auto stops = m_shimmerMaskGradient.ColorStops();
	stops.Clear();
	if (!gradientStops)
		return;
	for (auto gradientStop : gradientStops)
		stops.Append(m_compositor.CreateColorGradientStop(gradientStop.Offset(), gradientStop.Color()));
}

winrt::WinUINamespace::UI::Composition::ShapeVisual ShimmerAnimationMember::GetVisual(
	winrt::Windows::Foundation::Numerics::float2 size,
	float cornerRadius
)
{
	if (m_shapeVisual)
		return m_shapeVisual;

	m_rectangleGeometry.Size(size);
	m_rectangleGeometry.CornerRadius({ cornerRadius / 2, cornerRadius / 2 });
	auto spriteShape = m_compositor.CreateSpriteShape(m_rectangleGeometry);
	spriteShape.FillBrush(m_shimmerMaskGradient);

	m_shapeVisual = m_compositor.CreateShapeVisual();
	m_shapeVisual.Shapes().Append(spriteShape);

	m_shimmerMaskGradient.StartAnimation(L"StartPoint", m_gradientStartPointAnimation);
	m_shimmerMaskGradient.StartAnimation(L"EndPoint", m_gradientStopPointAnimation);

	m_shapeVisual.Size(size);
	return m_shapeVisual;
}

void ShimmerAnimationMember::SetSize(winrt::Windows::Foundation::Numerics::float2 size)
{
	m_rectangleGeometry.Size(size);
	m_shapeVisual.Size(size);
}

void ShimmerAnimationMember::StopAnimation()
{
	m_shimmerMaskGradient.StopAnimation(L"StartPoint");
	m_shimmerMaskGradient.StopAnimation(L"EndPoint");
}

ShimmerAnimationMember::~ShimmerAnimationMember()
{
	StopAnimation();
}


