#pragma once

#include "TenMicaWindow.g.h"
#include "WallpaperManager.h"
#include <winrt/Microsoft.UI.Composition.h>
#include <d2d1_1.h>
#include "CombinedWallpaper.h"

namespace winrt::WinUI3Example::implementation
{
    struct TenMicaWindow : TenMicaWindowT<TenMicaWindow>
    {
        TenMicaWindow();
        ~TenMicaWindow();

        void Draw();

    private:
        void createBrush(ID2D1DeviceContext* d2dContext);
		winrt::Microsoft::UI::Composition::CompositionDrawingSurface m_drawingSurface{ nullptr };
		WallpaperManager m_wallpaperManager;
        CombinedWallpaper m_combinedWallpaper;
        //from Master Dai's figma
        //winrt::com_ptr<ID2D1Effect> m_blurEffect;
        //winrt::com_ptr<ID2D1Effect> m_floodEffect;
        //winrt::com_ptr<ID2D1Effect> m_finalBlend;

        //from Ahmed
        winrt::com_ptr<ID2D1Effect> m_blurEffect;
        winrt::com_ptr<ID2D1Effect> m_luminosityColorEffect;
		winrt::com_ptr<ID2D1Effect> m_luminosityBlendEffect;
        winrt::com_ptr<ID2D1Effect> m_tintColorEffect;
        winrt::com_ptr<ID2D1Effect> m_finalBlend;
        winrt::Microsoft::UI::Composition::Compositor compositor{ nullptr };
        winrt::Microsoft::UI::Composition::CompositionEffectBrush crossFadeBrush{ nullptr };
        winrt::Microsoft::UI::Composition::CompositionSurfaceBrush m_surfaceBrush{ nullptr };
        void createEffects(ID2D1DeviceContext* d2dContext);

        // Win32 subclassing for window move interception
        HWND m_hwnd{ nullptr };
        UINT m_dpi{ 96 };
        static LRESULT CALLBACK SubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
        void updateBrushOffset();
        void updateBrushOffset(int windowX, int windowY);
    public:
        void Window_Activated(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);
    };
}

namespace winrt::WinUI3Example::factory_implementation
{
    struct TenMicaWindow : TenMicaWindowT<TenMicaWindow, implementation::TenMicaWindow>
    {
    };
}
