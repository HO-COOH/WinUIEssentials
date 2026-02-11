#pragma once
#include <winrt/base.h>
#include <wil/com.h>

struct IWICFormatConverter;

struct WallpaperInfo
{
	winrt::com_ptr<IWICFormatConverter> wallpaper;
	wil::unique_cotaskmem_string path;
	RECT rect;
};
