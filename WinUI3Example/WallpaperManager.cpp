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

winrt::com_ptr<IWICFormatConverter> WallpaperManager::Get()
{
    if (!m_desktopWallpaper)
        init();

    wil::unique_cotaskmem_string monitorId, path;
    winrt::check_hresult(m_desktopWallpaper->GetMonitorDevicePathAt(0, monitorId.put()));
	winrt::check_hresult(m_desktopWallpaper->GetWallpaper(monitorId.get(), path.put()));

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
	winrt::com_ptr<IWICFormatConverter> converter;
	winrt::check_hresult(m_wicFactory->CreateFormatConverter(converter.put()));
    winrt::check_hresult(converter->Initialize(
        frame.get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherType::WICBitmapDitherTypeNone,
        nullptr,
        0.0,
        WICBitmapPaletteType::WICBitmapPaletteTypeMedianCut
    ));
    return converter;
}
