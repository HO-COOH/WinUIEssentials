#include "pch.h"
#include "InAppAcrylicVisual.h"
#if __has_include("InAppAcrylicVisual.g.cpp")
#include "InAppAcrylicVisual.g.cpp"
#endif
#include "GaussianBlurEffectInterop.h"
#include "BlendEffectInterop.h"

namespace winrt::WinUI3Package::implementation
{
	InAppAcrylicVisual::InAppAcrylicVisual()
	{
		ActualThemeChanged([this](auto&&...)
		{
			//Brushes may not be created yet
			if (m_tintBrush)
				updateBrushColor();
		});

		m_backdropLink.ExternalBackdropBorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
		m_backdropLink.SystemBackdrop(createFinalBrush());
		m_placementVisual = m_backdropLink.PlacementVisual();
		BindPlacementVisual();
		m_placementVisual.BorderMode(winrt::Microsoft::UI::Composition::CompositionBorderMode::Soft);
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(*this, m_placementVisual);
	}

	void InAppAcrylicVisual::updateBrushColor()
	{
		auto const actualTheme = ActualTheme();
		m_luminosityBrush.Color(luminosityBrushColor(actualTheme));
		m_tintBrush.Color(tintBrushColor(actualTheme));
	}

	winrt::Windows::UI::Composition::CompositionBrush InAppAcrylicVisual::createFinalBrush()
	{
		auto const actualTheme = ActualTheme();
		winrt::Windows::UI::Composition::Compositor compositor;
		m_tintBrush = compositor.CreateColorBrush(tintBrushColor(actualTheme));
		m_luminosityBrush = compositor.CreateColorBrush(luminosityBrushColor(actualTheme));

		auto colorAnimation = compositor.CreateColorKeyFrameAnimation();
		colorAnimation.Target(L"Color");
		colorAnimation.InsertExpressionKeyFrame(1.f, L"this.FinalValue");
		colorAnimation.Duration(std::chrono::milliseconds{ 250 });
		auto implicitAnimations = compositor.CreateImplicitAnimationCollection();
		implicitAnimations.Insert(L"Color", colorAnimation);
		m_tintBrush.ImplicitAnimations(implicitAnimations);
		m_luminosityBrush.ImplicitAnimations(implicitAnimations);

		auto blurEffect = winrt::make_self<GaussianBlurEffectInterop>(30.0f, L"Backdrop");
		auto luminosityEffect = winrt::make_self<BlendEffectInterop>(
			D2D1_BLEND_MODE_COLOR, 
			*blurEffect,
			L"Luminosity"
		);
		auto tintEffect = winrt::make_self<BlendEffectInterop>(
			D2D1_BLEND_MODE_LUMINOSITY,
			*luminosityEffect,
			L"Tint"
		);
		auto finalBrush = compositor.CreateEffectFactory(*tintEffect).CreateBrush();
		finalBrush.SetSourceParameter(L"Backdrop", compositor.CreateBackdropBrush());
		finalBrush.SetSourceParameter(L"Luminosity", m_luminosityBrush);
		finalBrush.SetSourceParameter(L"Tint", m_tintBrush);
		return finalBrush;
	}


}
