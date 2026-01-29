#pragma once
#include <winrt/base.h>
#include <wincodec.h>
#include <ShlObj_core.h>
#include <boost/container/small_vector.hpp>

struct IDesktopWallpaper;
struct IWICImagingFactory;
struct IWICBitmapDecoder;
struct IWICFormatConverter;

struct WallpaperInfo
{
	winrt::com_ptr<IWICFormatConverter> wallpaper;
	RECT rect;
};

class WallpaperManager
{
	winrt::com_ptr<IDesktopWallpaper> m_desktopWallpaper;
	winrt::com_ptr<IWICImagingFactory> m_wicFactory;
	void init();

	constexpr static auto MonitorCountEstimate = 4;
public:
	[[nodiscard]] boost::container::small_vector<WallpaperInfo, MonitorCountEstimate> Get();
	[[nodiscard]] DESKTOP_WALLPAPER_POSITION Position();
};

