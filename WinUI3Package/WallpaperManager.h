#pragma once
#include <winrt/base.h>
#include <wincodec.h>
#include <ShlObj_core.h>
#include <boost/container/small_vector.hpp>
#include <wil/com.h>
#include "WallpaperInfo.h"

class WallpaperManager
{
	constexpr static auto MonitorCountEstimate = 4;

	winrt::com_ptr<IDesktopWallpaper> m_desktopWallpaper;
	winrt::com_ptr<IWICImagingFactory> m_wicFactory;
	boost::container::small_vector<WallpaperInfo, MonitorCountEstimate> m_wallpaperInfos;

	UINT getMonitorCount();
public:
	WallpaperManager();
	[[nodiscard]] bool UpdatedNeeded();
	[[nodiscard]] boost::container::small_vector<WallpaperInfo, MonitorCountEstimate> const& Get() const;
	[[nodiscard]] DESKTOP_WALLPAPER_POSITION Position();

	static WallpaperManager& GetInstance(bool recreate = false);
};

