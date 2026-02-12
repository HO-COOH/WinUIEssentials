#pragma once
#include <winrt/Windows.UI.Composition.h>
#include "CombinedWallpaperSurfaces.h"
#include "TenMicaEffect.h"

class WallpaperManager;

class TenMicaEffectFactory
{
	winrt::Windows::UI::Composition::Compositor compositor;

	winrt::Windows::UI::Composition::ImplicitAnimationCollection m_implicitInactiveBrushAnimation = compositor.CreateImplicitAnimationCollection();

	winrt::Windows::UI::Composition::CompositionEffectFactory themeCrossFadeEffectFactory{ nullptr };
	winrt::Windows::UI::Composition::CompositionEffectFactory finalEffectFactory{ nullptr };
	
	CombinedWallpaperSurfaces m_wallpaperSurfaces;

	void createFactory();
public:

	winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeForwardAnimation = compositor.CreateScalarKeyFrameAnimation();
	winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeBackwardAnimation = compositor.CreateScalarKeyFrameAnimation();

	TenMicaEffectFactory();

	[[nodiscard]] TenMicaEffect Get();
	[[nodiscard]] static TenMicaEffectFactory& GetFactory(bool recreate = false);
	void Redraw(WallpaperManager& wallpaperManager);
};