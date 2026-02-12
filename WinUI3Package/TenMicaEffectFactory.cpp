#include "pch.h"
#include "TenMicaEffectFactory.h"
#include "TenMicaConstants.h"
#include "CrossFadeEffectInterop.h"
#include "WallpaperManager.h"

void TenMicaEffectFactory::createFactory()
{
	auto themeCrossFadeEffect = winrt::make_self<CrossFadeInterop>();
	themeCrossFadeEffect->CrossFade = 1.0f; // start dark
	themeCrossFadeEffect->Name(L"ThemeFade");
	themeCrossFadeEffect->Source1 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Light" };
	themeCrossFadeEffect->Source2 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Dark" };
	themeCrossFadeEffectFactory = compositor.CreateEffectFactory(*themeCrossFadeEffect, { L"ThemeFade.CrossFade" });

	auto crossFadeEffectInterop = winrt::make_self<CrossFadeInterop>();
	crossFadeEffectInterop->CrossFade = 0.0f;
	crossFadeEffectInterop->Name(L"CrossFade");
	crossFadeEffectInterop->Source1 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Source1" };
	crossFadeEffectInterop->Source2 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Source2" };
	finalEffectFactory = compositor.CreateEffectFactory(*crossFadeEffectInterop, { L"CrossFade.CrossFade" });

	auto colorAnimation = compositor.CreateColorKeyFrameAnimation();
	colorAnimation.InsertExpressionKeyFrame(1.f, L"this.FinalValue");
	colorAnimation.Target(L"Color");
	m_implicitInactiveBrushAnimation.Insert(L"Color", colorAnimation);
}

TenMicaEffectFactory::TenMicaEffectFactory()
{
	auto linearEase = compositor.CreateLinearEasingFunction();

	m_crossFadeForwardAnimation.InsertKeyFrame(1.f, 0.f, linearEase);
	m_crossFadeForwardAnimation.Duration(TenMicaConstants::AnimationDuration);

	m_crossFadeBackwardAnimation = compositor.CreateScalarKeyFrameAnimation();
	m_crossFadeBackwardAnimation.InsertKeyFrame(1.f, 1.f, linearEase);
	m_crossFadeBackwardAnimation.Duration(TenMicaConstants::AnimationDuration);
}

TenMicaEffect TenMicaEffectFactory::Get()
{
	if (!themeCrossFadeEffectFactory)
		createFactory();

	auto& wallpaperManager = WallpaperManager::GetInstance();
	std::ignore = wallpaperManager.UpdatedNeeded();

	TenMicaEffect effect
	{
		.m_themeCrossFadeBrush = themeCrossFadeEffectFactory.CreateBrush(),
		.m_finalCrossFadeBrush = finalEffectFactory.CreateBrush(),
		.m_inactiveBrush = compositor.CreateColorBrush(TenMicaConstants::WinUI::LuminosityColorDark),
		.m_lightBrush = m_wallpaperSurfaces.DrawToSurfaceWithNewBrush(compositor, wallpaperManager, true),
		.m_darkBrush = m_wallpaperSurfaces.DrawToSurfaceWithNewBrush(compositor, wallpaperManager, false)
	};

	effect.m_themeCrossFadeBrush.SetSourceParameter(L"Light", effect.m_lightBrush);
	effect.m_themeCrossFadeBrush.SetSourceParameter(L"Dark", effect.m_darkBrush);
	
	effect.m_inactiveBrush.ImplicitAnimations(m_implicitInactiveBrushAnimation);
	
	effect.m_finalCrossFadeBrush = finalEffectFactory.CreateBrush();
	effect.m_finalCrossFadeBrush.SetSourceParameter(L"Source1", effect.m_themeCrossFadeBrush);
	effect.m_finalCrossFadeBrush.SetSourceParameter(L"Source2", effect.m_inactiveBrush);
	
	return effect;
}

TenMicaEffectFactory& TenMicaEffectFactory::GetFactory(bool recreate)
{
	thread_local std::optional<TenMicaEffectFactory> s_factory;
	if (!s_factory || recreate)
		s_factory.emplace();
	return *s_factory;
}

void TenMicaEffectFactory::Redraw(WallpaperManager& wallpaperManager)
{
	m_wallpaperSurfaces.DrawToSurface(compositor, wallpaperManager, true);
	m_wallpaperSurfaces.DrawToSurface(compositor, wallpaperManager, false);
}
