#pragma once
#include <winrt/base.h>
#include <wincodec.h>
#include <ShlObj_core.h>
#include <boost/container/small_vector.hpp>
#include "WallpaperInfo.h"
#include "TenMicaRegistry.h"

class WallpaperManager
{
	winrt::com_ptr<IDesktopWallpaper> m_desktopWallpaper;
	winrt::com_ptr<IWICImagingFactory> m_wicFactory;
	boost::container::small_vector<WallpaperInfo, TenMicaRegistry::MonitorCountEstimate> m_wallpaperInfos;
	DESKTOP_WALLPAPER_POSITION m_position{ DWPOS_FILL };
	bool m_forceUpdate{};

	HRESULT callDesktopWallpaper(auto method, auto&&... args);
	UINT getMonitorCount();
	wil::unique_cotaskmem_string getMonitorDevicePathAt(UINT index);
	bool getMonitorRect(PCWSTR monitorId, RECT& rect);
	wil::unique_cotaskmem_string getWallpaper(PCWSTR monitorId);

	winrt::com_ptr<IWICFormatConverter> createSolidColorWallpaper(
		RECT const& rect,
		COLORREF color
	);
public:
	WallpaperManager();
	[[nodiscard]] bool UpdatedNeeded();
	[[nodiscard]] boost::container::small_vector<WallpaperInfo, TenMicaRegistry::MonitorCountEstimate> const& Get() const;
	[[nodiscard]] DESKTOP_WALLPAPER_POSITION Position();
};
