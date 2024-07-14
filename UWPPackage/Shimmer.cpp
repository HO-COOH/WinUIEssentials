#include "pch.h"
#include "Shimmer.h"
#if __has_include("Shimmer.g.cpp")
#include "Shimmer.g.cpp"
#endif
#include <winrt/Windows.UI.Xaml.Hosting.h>

namespace winrt::UWPPackage::implementation
{
	winrt::Windows::UI::Xaml::DependencyProperty Shimmer::s_isLoadingProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"IsLoading",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				winrt::box_value(false)
			}
		);
	bool Shimmer::IsLoading()
	{
		return winrt::unbox_value<bool>(GetValue(IsLoadingProperty()));
	}
	void Shimmer::IsLoading(bool value)
	{
		SetValue(IsLoadingProperty(), winrt::box_value(value));
	}
	winrt::Windows::UI::Xaml::DependencyProperty Shimmer::IsLoadingProperty()
	{
		return s_isLoadingProperty;
	}

	void Shimmer::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_container = GetTemplateChild(L"Container").as<winrt::Windows::UI::Xaml::FrameworkElement>();
		m_container.Loaded([this](auto&&...) {	startAnimation(); });
	}

	void Shimmer::startAnimation()
	{
		m_animation.emplace(
			winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(m_container).Compositor(),
			std::chrono::milliseconds{ 1600 }
		);
		m_animation->SetGradientStops(LightColors, GradientStopOffset);
		auto size = m_container.ActualSize();
		winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_container, m_animation->GetVisual(size, 8.f));
	}

	void Shimmer::AnimationMember::appendGradientStop(winrt::Windows::UI::Color color, float offset)
	{
		appendGradientStop(m_compositor.CreateColorGradientStop(offset, color));
	}

	void Shimmer::AnimationMember::appendGradientStop(
		winrt::Windows::UI::Composition::CompositionColorGradientStop const& gradientStop)
	{
		m_shimmerMaskGradient.ColorStops().Append(gradientStop);
	}

	Shimmer::AnimationMember::AnimationMember(
		winrt::Windows::UI::Composition::Compositor const& compositor,
		winrt::Windows::Foundation::TimeSpan duration) :
		m_gradientStartPointAnimation{compositor.CreateVector2KeyFrameAnimation()},
		m_gradientStopPointAnimation{compositor.CreateVector2KeyFrameAnimation()},
		m_rectangleGeometry{compositor.CreateRoundedRectangleGeometry()},
		m_shimmerMaskGradient{compositor.CreateLinearGradientBrush() },
		m_compositor{compositor}
		//m_duration{duration}
	{
		m_gradientStartPointAnimation.Duration(duration);
		m_gradientStartPointAnimation.IterationBehavior(winrt::Windows::UI::Composition::AnimationIterationBehavior::Forever);
		m_gradientStartPointAnimation.InsertKeyFrame(0.0f, { InitialStartPointX, 0.0f });
		m_gradientStartPointAnimation.InsertKeyFrame(1.0f, {});

		m_gradientStopPointAnimation.Duration(duration);
		m_gradientStopPointAnimation.IterationBehavior(winrt::Windows::UI::Composition::AnimationIterationBehavior::Forever);
		m_gradientStopPointAnimation.InsertKeyFrame(0.0f, { 1.0f, 0.0f });
		m_gradientStopPointAnimation.InsertKeyFrame(1.0f, { -InitialStartPointX, 1.0f });



	}

	void Shimmer::AnimationMember::SetGradientStops(
		std::span<winrt::Windows::UI::Color const> gradientStops, 
		std::span<float const> gradientOffsets)
	{
		assert(gradientStops.size() == gradientOffsets.size());
		for (auto i = 0; i < gradientStops.size(); ++i)
			appendGradientStop(gradientStops[i], gradientOffsets[i]);
	}

	winrt::Windows::UI::Composition::ShapeVisual Shimmer::AnimationMember::GetVisual(
		winrt::Windows::Foundation::Numerics::float2 size,
		float cornerRadius
	)
	{
		m_rectangleGeometry.Size(size);
		m_rectangleGeometry.CornerRadius({ cornerRadius, cornerRadius });
		auto spriteShape = m_compositor.CreateSpriteShape(m_rectangleGeometry);
		spriteShape.FillBrush(m_shimmerMaskGradient);
		
		auto shapeVisual = m_compositor.CreateShapeVisual();
		shapeVisual.Shapes().Append(spriteShape);

		m_shimmerMaskGradient.StartAnimation(L"StartPoint", m_gradientStartPointAnimation);
		m_shimmerMaskGradient.StartAnimation(L"EndPoint", m_gradientStopPointAnimation);

		shapeVisual.Size(size);
		return shapeVisual;
	}


}
