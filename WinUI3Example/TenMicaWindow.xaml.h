#pragma once

#include "TenMicaWindow.g.h"
#include "WallpaperManager.h"
#include <winrt/Microsoft.UI.Composition.h>
#include <d2d1_1.h>

namespace winrt::WinUI3Example::implementation
{
    struct TenMicaWindow : TenMicaWindowT<TenMicaWindow>
    {
        TenMicaWindow();

        void Draw();

    private:
        void createBrush(ID2D1DeviceContext* d2dContext);
		winrt::Microsoft::UI::Composition::CompositionDrawingSurface m_drawingSurface{ nullptr };
		WallpaperManager m_wallpaperManager;

        //from Master Dai's figma
        //winrt::com_ptr<ID2D1Effect> m_scaleEffect;
		//winrt::com_ptr<ID2D1Effect> m_blurEffect;
        //winrt::com_ptr<ID2D1Effect> m_floodEffect;
        //winrt::com_ptr<ID2D1Effect> m_finalBlend;

        //from Ahmed
		winrt::com_ptr<ID2D1Effect> m_scaleEffect;
        winrt::com_ptr<ID2D1Effect> m_blurEffect;
        winrt::com_ptr<ID2D1Effect> m_luminosityColorEffect;
		winrt::com_ptr<ID2D1Effect> m_luminosityBlendEffect;
        winrt::com_ptr<ID2D1Effect> m_tintColorEffect;
        winrt::com_ptr<ID2D1Effect> m_finalBlend;

        void createEffects(ID2D1DeviceContext* d2dContext);

        winrt::com_ptr<ID2D1Bitmap1> wallpaperBitmap;
        void combinedWallpaper(ID2D1DeviceContext* d2dContext);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TenMicaWindow : TenMicaWindowT<TenMicaWindow, implementation::TenMicaWindow>
    {
    };
}
