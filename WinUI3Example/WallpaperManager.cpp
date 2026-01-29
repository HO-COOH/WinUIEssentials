#include "pch.h"
#include "WallpaperManager.h"
#include <ShObjIdl_core.h>
#include <wil/com.h>
#include <wincodec.h>

void WallpaperManager::init()
{
    winrt::check_hresult(CoCreateInstance(
        CLSID_DesktopWallpaper,
        nullptr,
        CLSCTX_ALL,
        IID_PPV_ARGS(m_desktopWallpaper.put())
	));

    winrt::check_hresult(CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(m_wicFactory.put())
	));
}

boost::container::small_vector<WallpaperInfo, WallpaperManager::MonitorCountEstimate> WallpaperManager::Get()
{
    if (!m_desktopWallpaper)
        init();

    boost::container::small_vector<WallpaperInfo, MonitorCountEstimate> result;
    UINT count{};
    winrt::check_hresult(m_desktopWallpaper->GetMonitorDevicePathCount(&count));
    
    wil::unique_cotaskmem_string monitorId, path;

    for (UINT i = 0; i < count; ++i)
    {
        WallpaperInfo info;

        winrt::check_hresult(m_desktopWallpaper->GetMonitorDevicePathAt(i, monitorId.put()));
        winrt::check_hresult(m_desktopWallpaper->GetWallpaper(monitorId.get(), path.put()));

        //the `count` will contain detached monitors with a wallpaper assigned. 
        //See https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-idesktopwallpaper-getmonitorrect
        //We rule out this case first
        if (FAILED(m_desktopWallpaper->GetMonitorRECT(monitorId.get(), &info.rect)))
            continue;

        winrt::com_ptr<IWICBitmapDecoder> decoder;
        winrt::check_hresult(m_wicFactory->CreateDecoderFromFilename(
            path.get(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            decoder.put()
        ));
        winrt::com_ptr<IWICBitmapFrameDecode> frame;
        winrt::check_hresult(decoder->GetFrame(0, frame.put()));
        winrt::check_hresult(m_wicFactory->CreateFormatConverter(info.wallpaper.put()));
        winrt::check_hresult(info.wallpaper->Initialize(
            frame.get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherType::WICBitmapDitherTypeNone,
            nullptr,
            0.0,
            WICBitmapPaletteType::WICBitmapPaletteTypeMedianCut
        ));

        result.emplace_back(std::move(info));
    }

    return result;
}

DESKTOP_WALLPAPER_POSITION WallpaperManager::Position()
{
    if (!m_desktopWallpaper)
        init();

    DESKTOP_WALLPAPER_POSITION position;
    winrt::check_hresult(m_desktopWallpaper->GetPosition(&position));
    return position;
}