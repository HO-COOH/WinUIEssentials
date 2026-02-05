#pragma once
#include <d2d1_1.h>
#include <ShlObj_core.h>
#include "D2D1DeviceContextState.h"
#include "WallpaperManager.h"

struct WallpaperInfo;
struct IWICFormatConverter;

class CombinedWallpaper
{
	winrt::com_ptr<ID2D1Bitmap1> m_combinedWallpaperBitmap;
	D2D1_SIZE_U m_currentSize{};

	void createNewBitmapIfSizeChanged(ID2D1DeviceContext* d2dContext);

	//draw_span need to use member size, so not static
	void draw_span(ID2D1DeviceContext* d2dContext, WallpaperInfo& wallpaper);

	static void draw_fill(ID2D1DeviceContext* d2dContext, WallpaperInfo& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_tile(ID2D1DeviceContext* d2dContext, WallpaperInfo& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_center(ID2D1DeviceContext* d2dContext, WallpaperInfo& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_stretch(ID2D1DeviceContext* d2dContext, WallpaperInfo& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static void draw_fit(ID2D1DeviceContext* d2dContext, WallpaperInfo& wallpaperInfo, ID2D1Bitmap1* wallpaper);
	static winrt::com_ptr<ID2D1Bitmap1> createBitmap(ID2D1DeviceContext* d2dContext, IWICFormatConverter* converter);
	static void drawBitmapImpl(ID2D1DeviceContext* d2dContext, ID2D1Bitmap* bitmap, D2D1_RECT_F rect);
public:
	ID2D1Bitmap1* Draw(
		auto&& wallpapers,
		DESKTOP_WALLPAPER_POSITION position,
		ID2D1DeviceContext* d2dContext
	)
	{
		createNewBitmapIfSizeChanged(d2dContext);

		D2D1DeviceContextState savedState{ d2dContext };
		d2dContext->SetTarget(m_combinedWallpaperBitmap.get());
		d2dContext->Clear(D2D1::ColorF{ 0.0f, 0.0f, 0.0f, 1.0f });

		void(*drawLogic)(ID2D1DeviceContext*, WallpaperInfo&, ID2D1Bitmap1*) {};

		switch (position)
		{
		case DESKTOP_WALLPAPER_POSITION::DWPOS_SPAN:
			if (!wallpapers.empty())
				draw_span(d2dContext, wallpapers.front());
			return m_combinedWallpaperBitmap.get();
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

		for (auto& wallpaperInfo : wallpapers)
		{
			auto wallpaperBitmap = createBitmap(d2dContext, wallpaperInfo.wallpaper.get());
			(*drawLogic)(d2dContext, wallpaperInfo, wallpaperBitmap.get());
		}
		return m_combinedWallpaperBitmap.get();
	}
};
