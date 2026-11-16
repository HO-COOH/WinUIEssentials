#include "pch.h"
#include "WallpaperManager.h"
#include <ShObjIdl_core.h>
#include <wil/com.h>
#include "TenMicaRegistry.h"
#include <wincodec.h>
#include <utility>

struct DesktopWallpaperUnavailable {};

constexpr bool isRpcDisconnected(HRESULT hr) noexcept
{
    return (hr == HRESULT_FROM_WIN32(RPC_S_SERVER_UNAVAILABLE) ||
        hr == HRESULT_FROM_WIN32(RPC_S_CALL_FAILED) ||
        hr == HRESULT_FROM_WIN32(RPC_S_CALL_FAILED_DNE) ||
        hr == HRESULT_FROM_WIN32(RPC_S_UNKNOWN_IF) ||
        hr == RPC_E_DISCONNECTED ||
        hr == RPC_E_SERVER_DIED ||
        hr == RPC_E_SERVER_DIED_DNE ||
        hr == CO_E_OBJNOTCONNECTED
    );
}


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

HRESULT WallpaperManager::callDesktopWallpaper(auto method, auto&&... args)
{
    if (!m_desktopWallpaper)
    {
        m_desktopWallpaper = winrt::try_create_instance<IDesktopWallpaper>(CLSID_DesktopWallpaper, CLSCTX_ALL);
        if (!m_desktopWallpaper)
            throw DesktopWallpaperUnavailable{};
    }

    auto hr = (m_desktopWallpaper.get()->*method)(args...);
    if (isRpcDisconnected(hr))
    {
        m_desktopWallpaper = winrt::try_create_instance<IDesktopWallpaper>(CLSID_DesktopWallpaper, CLSCTX_ALL);
        if (!m_desktopWallpaper)
            throw DesktopWallpaperUnavailable{};
        hr = (m_desktopWallpaper.get()->*method)(args...);
        if (isRpcDisconnected(hr))
        {
            m_desktopWallpaper = nullptr;
            throw DesktopWallpaperUnavailable{};
        }
    }
    return hr;
}

WallpaperManager::WallpaperManager() :
    m_desktopWallpaper{ winrt::create_instance<IDesktopWallpaper>(CLSID_DesktopWallpaper, CLSCTX_ALL) },
    m_wicFactory{ winrt::create_instance<IWICImagingFactory>(CLSID_WICImagingFactory, CLSCTX_INPROC_SERVER) }
{
}

UINT WallpaperManager::getMonitorCount()
{
    //I found this could sometimes return 0 monitors when I absolutely have 1. Better print a log when in debug mode
    UINT count{};
    winrt::check_hresult(callDesktopWallpaper(&IDesktopWallpaper::GetMonitorDevicePathCount, &count));
#if (defined DEBUG) || (defined _DEBUG)
    OutputDebugString(std::format(L"TenMica backdrop get: {} monitors.\n", count).data());
#endif
    return count;
}

wil::unique_cotaskmem_string WallpaperManager::getMonitorDevicePathAt(UINT index)
{
    wil::unique_cotaskmem_string monitorId;
    winrt::check_hresult(callDesktopWallpaper(&IDesktopWallpaper::GetMonitorDevicePathAt, index, monitorId.put()));
    return monitorId;
}

bool WallpaperManager::getMonitorRect(PCWSTR monitorId, RECT& rect)
{
    return SUCCEEDED(callDesktopWallpaper(&IDesktopWallpaper::GetMonitorRECT, monitorId, &rect));
}

wil::unique_cotaskmem_string WallpaperManager::getWallpaper(PCWSTR monitorId)
{
    wil::unique_cotaskmem_string path;
    winrt::check_hresult(callDesktopWallpaper(&IDesktopWallpaper::GetWallpaper, monitorId, path.put()));
    return path;
}

bool WallpaperManager::UpdatedNeeded()
{
    bool updateNeeded = std::exchange(m_forceUpdate, false);
    try
    {
        auto const count = getMonitorCount();
        auto const previousCount = m_wallpaperInfos.size();
        if (count != previousCount)
        {
            updateNeeded = true;
            m_wallpaperInfos.resize(count);
        }

        for (UINT i = 0; i < count; ++i)
        {
            WallpaperInfo info;
            auto const monitorId = getMonitorDevicePathAt(i);

            //the `count` will contain detached monitors with a wallpaper assigned. 
            //See https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-idesktopwallpaper-getmonitorrect
            //We rule out this case first
            if (!getMonitorRect(monitorId.get(), info.rect))
                continue;

            info.path = getWallpaper(monitorId.get());
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

            //The wallpaper path returned by IDesktopWallpaper::GetWallpaper can point to a file that has deleted
            //But wallpaper uses TranscodedWallpaper, so it still displays normally, we need to fallback in this case
            winrt::com_ptr<IWICBitmapDecoder> decoder;
            if (auto const hr = m_wicFactory->CreateDecoderFromFilename(
                info.path.get(),
                nullptr,
                GENERIC_READ,
                WICDecodeMetadataCacheOnLoad,
                decoder.put()
            ); FAILED(hr))
            {
                info.path.reset();
                info.wallpaper = createSolidColorWallpaper(info.rect, info.solidColor);
                m_wallpaperInfos[i] = std::move(info);
#if (defined DEBUG) || (defined _DEBUG)
                OutputDebugString(std::format(L"[TenMica] Failed to open wallpaper file: {}, hr={}\n", i, info.path.get(), hr).data());
#endif
                continue;
            }
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
    catch (DesktopWallpaperUnavailable const&)
    {
        if (updateNeeded)
            m_forceUpdate = true;
        return false;
    }
}

boost::container::small_vector<WallpaperInfo, TenMicaRegistry::MonitorCountEstimate> const& WallpaperManager::Get() const
{
    return m_wallpaperInfos;
}

DESKTOP_WALLPAPER_POSITION WallpaperManager::Position()
{
    try
    {
        DESKTOP_WALLPAPER_POSITION position;
        winrt::check_hresult(callDesktopWallpaper(&IDesktopWallpaper::GetPosition, &position));
        m_position = position;
    }
    catch (DesktopWallpaperUnavailable const&)
    {
    }
    return m_position;
}

