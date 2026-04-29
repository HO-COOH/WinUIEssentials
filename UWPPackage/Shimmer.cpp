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
				winrt::box_value(false),
				[](winrt::Windows::UI::Xaml::DependencyObject const& shimmer, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const& args)
				{
					auto self = winrt::get_self<Shimmer>(shimmer.as<UWPPackage::Shimmer>());
					winrt::unbox_value<bool>(args.NewValue()) ? self->loadShimmer() : self->loadContent();
				}
			}
		);

	winrt::Windows::UI::Xaml::DependencyProperty Shimmer::s_gradientStopsProperty =
		winrt::Windows::UI::Xaml::DependencyProperty::Register(
			L"GradientStops",
			winrt::xaml_typename<winrt::Windows::UI::Xaml::Media::GradientStopCollection>(),
			winrt::xaml_typename<class_type>(),
			winrt::Windows::UI::Xaml::PropertyMetadata{
				nullptr,
				[](winrt::Windows::UI::Xaml::DependencyObject const& shimmer, winrt::Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&)
				{
					winrt::get_self<Shimmer>(shimmer.as<UWPPackage::Shimmer>())->applyGradientStops();
				}
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

	winrt::Windows::UI::Xaml::Media::GradientStopCollection Shimmer::GradientStops()
	{
		return GetValue(GradientStopsProperty()).try_as<winrt::Windows::UI::Xaml::Media::GradientStopCollection>();
	}

	void Shimmer::GradientStops(winrt::Windows::UI::Xaml::Media::GradientStopCollection const& value)
	{
		SetValue(GradientStopsProperty(), value);
	}

	winrt::Windows::UI::Xaml::DependencyProperty Shimmer::GradientStopsProperty()
	{
		return s_gradientStopsProperty;
	}

	void Shimmer::OnApplyTemplate()
	{
		base_type::OnApplyTemplate();
		m_loaded = true;

		m_presenter = GetTemplateChild(L"ContentPresenter").as<winrt::Windows::UI::Xaml::Controls::ContentPresenter>();
		IsLoading() ? loadShimmer() : loadContent();
	}

	void Shimmer::startAnimation()
	{
		if (!m_loaded)
			return;

		m_animation.emplace(
			winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(m_animationContainer).Compositor(),
			std::chrono::milliseconds{ 1600 }
		);

		m_animation->SetGradientStops(GradientStops());
		winrt::Windows::Foundation::Numerics::float2 size{
			static_cast<float>(m_animationContainer.ActualWidth()),
			static_cast<float>(m_animationContainer.ActualHeight())
		};
		winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_animationContainer, m_animation->GetVisual(size, CornerRadius().TopLeft));
	}

	void Shimmer::applyGradientStops()
	{
		if (m_animation)
			m_animation->SetGradientStops(GradientStops());
	}

	void Shimmer::loadShimmer()
	{
		if (!m_loaded)
			return;
		if (!m_animationContainer)
		{
			m_animationContainer = GetTemplateChild(L"Container").as<winrt::Windows::UI::Xaml::FrameworkElement>();
			m_animationSizeChangedRevoker = m_animationContainer.SizeChanged(winrt::auto_revoke, [this](auto&&, winrt::Windows::UI::Xaml::SizeChangedEventArgs const& args)
			{
				if (m_animation)
					m_animation->SetSize(args.NewSize());
			});
		}
		if (m_presenter)
			m_presenter.Opacity(0);
		startAnimation();
	}

	void Shimmer::loadContent()
	{
		m_animation.reset();
		if (m_animationContainer)
			winrt::Windows::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(m_animationContainer, nullptr);
		if (m_presenter)
			m_presenter.Opacity(1.0);
	}

	Shimmer::AnimationMember::AnimationMember(
		winrt::Windows::UI::Composition::Compositor const& compositor,
		winrt::Windows::Foundation::TimeSpan duration) :
		m_gradientStartPointAnimation{ compositor.CreateVector2KeyFrameAnimation() },
		m_gradientStopPointAnimation{ compositor.CreateVector2KeyFrameAnimation() },
		m_rectangleGeometry{ compositor.CreateRoundedRectangleGeometry() },
		m_shimmerMaskGradient{ compositor.CreateLinearGradientBrush() },
		m_compositor{ compositor }
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

	void Shimmer::AnimationMember::SetGradientStops(winrt::Windows::UI::Xaml::Media::GradientStopCollection gradientStops)
	{
		auto stops = m_shimmerMaskGradient.ColorStops();
		stops.Clear();
		if (!gradientStops)
			return;
		for (auto gradientStop : gradientStops)
			stops.Append(m_compositor.CreateColorGradientStop(gradientStop.Offset(), gradientStop.Color()));
	}

	winrt::Windows::UI::Composition::ShapeVisual Shimmer::AnimationMember::GetVisual(
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

	void Shimmer::AnimationMember::SetSize(winrt::Windows::Foundation::Numerics::float2 size)
	{
		m_rectangleGeometry.Size(size);
		m_shapeVisual.Size(size);
	}

	void Shimmer::AnimationMember::StopAnimation()
	{
		m_shimmerMaskGradient.StopAnimation(L"StartPoint");
		m_shimmerMaskGradient.StopAnimation(L"EndPoint");
	}

	Shimmer::AnimationMember::~AnimationMember()
	{
		StopAnimation();
	}
}
