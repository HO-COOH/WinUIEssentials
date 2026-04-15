#include "pch.h"
#include "WallpaperManager.h"
#include <ShObjIdl_core.h>
#include <wil/com.h>
#include "TenMicaRegistry.h"
#include <wincodec.h>


winrt::com_ptr<IWICFormatConverter> WallpaperManager::createSolidColorWallpaper(
    RECT const& rect,
    COLORREF color)
{
    auto const width = static_cast<UINT>((std::max)(1L, rect.right - rect.left));
    auto const height = static_cast<UINT>((std::max)(1L, rect.bottom - rect.top));
    auto const stride = width * 4;
    std::vector<uint8_t> pixels(static_cast<size_t>(stride) * height, 0);

    auto const b = GetBValue(color);
    auto const g = GetGValue(color);
    auto const r = GetRValue(color);
    for (size_t i = 0; i < pixels.size(); i += 4)
    {
        pixels[i] = b;
        pixels[i + 1] = g;
        pixels[i + 2] = r;
        pixels[i + 3] = 0xFF;
    }

    winrt::com_ptr<IWICBitmap> bitmap;
    winrt::check_hresult(m_wicFactory->CreateBitmapFromMemory(
        width,
        height,
        GUID_WICPixelFormat32bppPBGRA,
        stride,
        static_cast<UINT>(pixels.size()),
        pixels.data(),
        bitmap.put()
    ));

    winrt::com_ptr<IWICFormatConverter> converter;
    winrt::check_hresult(m_wicFactory->CreateFormatConverter(converter.put()));
    winrt::check_hresult(converter->Initialize(
        bitmap.get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherType::WICBitmapDitherTypeNone,
        nullptr,
        0.0,
        WICBitmapPaletteType::WICBitmapPaletteTypeMedianCut
    ));
    return converter;
}

WallpaperManager::WallpaperManager()
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

UINT WallpaperManager::getMonitorCount()
{
    //I found this could sometimes return 0 monitors when I absolutely have 1. Better print a log when in debug mode
    UINT count{};
    winrt::check_hresult(m_desktopWallpaper->GetMonitorDevicePathCount(&count));
#if (defined DEBUG) || (defined _DEBUG)
    OutputDebugString(std::format(L"TenMica backdrop get: {} monitors.\n", count).data());
#endif
    return count;
}

bool WallpaperManager::UpdatedNeeded()
{
    auto const count = getMonitorCount();
    auto const previousCount = m_wallpaperInfos.size();
    bool updateNeeded = (count != previousCount);
    if (updateNeeded)
        m_wallpaperInfos.resize(count);

    wil::unique_cotaskmem_string monitorId;
    for (UINT i = 0; i < count; ++i)
    {
        WallpaperInfo info;

        winrt::check_hresult(m_desktopWallpaper->GetMonitorDevicePathAt(i, monitorId.put()));

        //the `count` will contain detached monitors with a wallpaper assigned. 
        //See https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-idesktopwallpaper-getmonitorrect
        //We rule out this case first
        if (FAILED(m_desktopWallpaper->GetMonitorRECT(monitorId.get(), &info.rect)))
            continue;

        winrt::check_hresult(m_desktopWallpaper->GetWallpaper(monitorId.get(), info.path.put()));
        info.solidColor = TenMicaRegistry::Background();

        bool const pathValid = info.path && info.path.get()[0] != L'\0';
        bool const isSamePath = i < previousCount &&
            memcmp(&info.rect, &m_wallpaperInfos[i].rect, sizeof(info.rect)) == 0 &&
            [pathValid, this, i, &info]
            {
                auto const& previousInfo = m_wallpaperInfos[i];
                bool const previousPathValid = previousInfo.path && previousInfo.path.get()[0] != L'\0';

                if (pathValid != previousPathValid)
                    return false;

                if (pathValid)
                    return std::wstring_view{ previousInfo.path.get() } == std::wstring_view{ info.path.get() };

                return previousInfo.solidColor == info.solidColor;
            }();
        
        if (isSamePath)
            continue;
        else
            updateNeeded = true;

#if (defined DEBUG) || (defined _DEBUG)
        OutputDebugString(std::format(L"[TenMica] monitor #{}: {}\n", i, info.path.get()).data());
#endif

        if (!pathValid)
        {
            info.wallpaper = createSolidColorWallpaper(info.rect, info.solidColor);
            m_wallpaperInfos[i] = std::move(info);
            continue;
        }

        winrt::com_ptr<IWICBitmapDecoder> decoder;
        winrt::check_hresult(m_wicFactory->CreateDecoderFromFilename(
            info.path.get(),
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

        m_wallpaperInfos[i] = std::move(info);
    }

    return updateNeeded;
}

boost::container::small_vector<WallpaperInfo, TenMicaRegistry::MonitorCountEstimate> const& WallpaperManager::Get() const
{
    return m_wallpaperInfos;
}

DESKTOP_WALLPAPER_POSITION WallpaperManager::Position()
{
    DESKTOP_WALLPAPER_POSITION position;
    winrt::check_hresult(m_desktopWallpaper->GetPosition(&position));
    return position;
}

