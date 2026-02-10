#include "pch.h"
#include "WallpaperManager.h"
#include <ShObjIdl_core.h>
#include <wil/com.h>
#include <wincodec.h>

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

        bool const isSamePath = (
            i < previousCount &&
            m_wallpaperInfos[i].path &&
            info.path &&
            std::wstring_view{ m_wallpaperInfos[i].path.get() } == std::wstring_view{ info.path.get() }
        );
        
        if (isSamePath)
            continue;
        else
            updateNeeded = true;

#if (defined DEBUG) || (defined _DEBUG)
        OutputDebugString(std::format(L"TenMica backdrop monitor #{}: {}\n", i, info.path.get()).data());
#endif

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

boost::container::small_vector<WallpaperInfo, WallpaperManager::MonitorCountEstimate> const& WallpaperManager::Get() const
{
    return m_wallpaperInfos;
}

DESKTOP_WALLPAPER_POSITION WallpaperManager::Position()
{
    DESKTOP_WALLPAPER_POSITION position;
    winrt::check_hresult(m_desktopWallpaper->GetPosition(&position));
    return position;
}

static std::optional<WallpaperManager> s_instance;
WallpaperManager& WallpaperManager::GetInstance()
{
    if (!s_instance)
        s_instance.emplace();

    return *s_instance;
}
