#pragma once
#include <winrt/base.h>
#include <wincodec.h>
#include <ShlObj_core.h>

struct IDesktopWallpaper;
struct IWICImagingFactory;
struct IWICBitmapDecoder;
struct IWICFormatConverter;

class WallpaperManager
{
	winrt::com_ptr<IDesktopWallpaper> m_desktopWallpaper;
	winrt::com_ptr<IWICImagingFactory> m_wicFactory;

	void init();
public:
	winrt::com_ptr<IWICFormatConverter> Get();
};

