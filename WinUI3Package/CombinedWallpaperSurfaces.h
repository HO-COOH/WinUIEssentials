#pragma once
#include "CombinedWallpaper.h"
#include <winrt/Windows.UI.Composition.h>
#include <d2d1_1.h>

class WallpaperManager;

class CombinedWallpaperSurfaces
{
	CombinedWallpaper m_combinedWallpaperLight;
	CombinedWallpaper m_combinedWallpaperDark;
	winrt::Windows::UI::Composition::CompositionDrawingSurface m_surfaceLight{ nullptr };
	winrt::Windows::UI::Composition::CompositionDrawingSurface m_surfaceDark{ nullptr };
	winrt::Windows::UI::Composition::CompositionGraphicsDevice graphicsDevice{ nullptr };
	winrt::com_ptr<ID2D1Effect> m_blurEffect;
	winrt::com_ptr<ID2D1Effect> m_finalBlend;
	winrt::com_ptr<ID2D1Effect> luminosityColorEffect;
	winrt::com_ptr<ID2D1Effect> luminosityBlendEffect;
	winrt::com_ptr<ID2D1Effect> tintColorEffect;

	void createD2DEffects(ID2D1DeviceContext* d2dContext);

	static winrt::Windows::UI::Composition::CompositionSurfaceBrush initSurfaceBrush(
		winrt::Windows::UI::Composition::Compositor const& compositor,
		winrt::Windows::UI::Composition::CompositionDrawingSurface const& surface
	);

	void drawToSurfaceImpl(
		bool isLight,
		WallpaperManager& wallpaper
	);

	void setEffectValues(bool isLight);
public:
	winrt::Windows::UI::Composition::CompositionSurfaceBrush DrawToSurfaceWithNewBrush(
		winrt::Windows::UI::Composition::Compositor const& compositor, 
		WallpaperManager& wallpaper, 
		bool isLight
	);

	void DrawToSurface(
		winrt::Windows::UI::Composition::Compositor const& compositor,
		WallpaperManager& wallpaper,
		bool isLight
	);
};

