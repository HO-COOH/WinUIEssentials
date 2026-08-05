#pragma once
#include <d2d1_1.h>
#include <ranges>
#include <ShlObj_core.h>
#include "D2D1DeviceContextState.h"
#include "WallpaperManager.h"
#include "AutoResizeBitmap.h"

struct WallpaperInfo;
struct IWICFormatConverter;

class CombinedWallpaper
{
	AutoResizeBitmap m_combinedWallpaperBitmap;

	//draw_span need to use member size, so not static
	void draw_span(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaper);

	static void draw_fill(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_tile(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_center(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_stretch(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_fit(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static winrt::com_ptr<ID2D1Bitmap1> createBitmap(ID2D1DeviceContext* d2dContext, IWICFormatConverter* converter);
	static void drawBitmapImpl(ID2D1DeviceContext* d2dContext, ID2D1Bitmap* bitmap, D2D1_RECT_F rect);
public:
	constexpr void Reset()
	{
		m_combinedWallpaperBitmap.Reset();
	}

	ID2D1Bitmap1* Draw(
		auto&& wallpapers,
		DESKTOP_WALLPAPER_POSITION position,
		D2D1_SIZE_U size,
		ID2D1DeviceContext* d2dContext
	)
	{
		auto target = m_combinedWallpaperBitmap.RecreateIfNeeded(d2dContext, size.width, size.height);

		D2D1DeviceContextState savedState{ d2dContext };
		d2dContext->SetTarget(target);
		d2dContext->SetTransform(D2D1::Matrix3x2F::Identity());
		d2dContext->Clear(D2D1::ColorF{ 0.0f, 0.0f, 0.0f, 1.0f });

		void(*drawLogic)(ID2D1DeviceContext*, WallpaperInfo const&, ID2D1Bitmap1*) {};

		switch (position)
		{
			case DESKTOP_WALLPAPER_POSITION::DWPOS_SPAN:
				if (!wallpapers.empty())
					draw_span(d2dContext, wallpapers.front());
				return m_combinedWallpaperBitmap.Get();
			case DESKTOP_WALLPAPER_POSITION::DWPOS_CENTER:
				drawLogic = &CombinedWallpaper::draw_center;
				break;
			case DESKTOP_WALLPAPER_POSITION::DWPOS_TILE:
				drawLogic = &CombinedWallpaper::draw_tile;
				break;
			case DESKTOP_WALLPAPER_POSITION::DWPOS_STRETCH:
				drawLogic = &CombinedWallpaper::draw_stretch;
				break;
			case DESKTOP_WALLPAPER_POSITION::DWPOS_FIT:
				drawLogic = &CombinedWallpaper::draw_fit;
				break;
			case DESKTOP_WALLPAPER_POSITION::DWPOS_FILL:
				drawLogic = &CombinedWallpaper::draw_fill;
				break;
		}

		for (auto& wallpaperInfo : wallpapers | std::views::filter([](auto const& w) { return static_cast<bool>(w.wallpaper); }))
		{
			auto wallpaperBitmap = createBitmap(d2dContext, wallpaperInfo.wallpaper.get());
			(*drawLogic)(d2dContext, wallpaperInfo, wallpaperBitmap.get());
		}
		return m_combinedWallpaperBitmap.Get();
	}
};
