#pragma once
#include <winrt/Windows.UI.Composition.h>
#include <memory>
#include "CombinedWallpaperSurfaces.h"
#include "TenMicaEffect.h"

#include "WallpaperManager.h"

class TenMicaEffectFactory : public std::enable_shared_from_this<TenMicaEffectFactory>
{
	winrt::Windows::UI::Composition::Compositor compositor;

	winrt::Windows::UI::Composition::ImplicitAnimationCollection m_implicitInactiveBrushAnimation = compositor.CreateImplicitAnimationCollection();

	winrt::Windows::UI::Composition::CompositionEffectFactory themeCrossFadeEffectFactory{ nullptr };
	winrt::Windows::UI::Composition::CompositionEffectFactory finalEffectFactory{ nullptr };
	
	CombinedWallpaperSurfaces m_wallpaperSurfaces;

	void createFactory();
public:
	WallpaperManager m_wallpaperManager;

	winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeForwardAnimation = compositor.CreateScalarKeyFrameAnimation();
	winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeBackwardAnimation = compositor.CreateScalarKeyFrameAnimation();

	TenMicaEffectFactory();

	[[nodiscard]] TenMicaEffect Get();
	[[nodiscard]] static std::shared_ptr<TenMicaEffectFactory> GetFactory();
	void Redraw();
	void OnDeviceLost(TenMicaEffect& effectToReset);
};