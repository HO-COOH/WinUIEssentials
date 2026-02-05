#pragma once

#include "TenMicaBackdrop.g.h"
#include <d2d1_1.h>
#include <winrt/Windows.UI.Composition.h>
#include "WallpaperManager.h"
#include "CombinedWallpaper.h"

namespace winrt::WinUI3Package::implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop>
    {
        TenMicaBackdrop() = default;

        winrt::Microsoft::UI::Xaml::FrameworkElement BindThemeTo();
        void BindThemeTo(winrt::Microsoft::UI::Xaml::FrameworkElement const value);

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot);

        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);
    private:
        winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement> m_bindThemeTo;
        winrt::Microsoft::UI::Xaml::FrameworkElement::ActualThemeChanged_revoker m_bindThemeRevoker;
        HWND m_hwnd{};

        winrt::com_ptr<ID2D1Effect> m_blurEffect;
        winrt::com_ptr<ID2D1Effect> m_luminosityColorEffect;
        winrt::com_ptr<ID2D1Effect> m_luminosityBlendEffect;
        winrt::com_ptr<ID2D1Effect> m_tintColorEffect;
        winrt::com_ptr<ID2D1Effect> m_finalBlend;
        winrt::Windows::UI::Composition::Compositor compositor{ nullptr };
        winrt::Windows::UI::Composition::CompositionDrawingSurface m_drawingSurface{ nullptr };
        winrt::Windows::UI::Composition::CompositionEffectBrush crossFadeBrush{ nullptr };
        winrt::Windows::UI::Composition::CompositionSurfaceBrush m_surfaceBrush{ nullptr };
        winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeForwardAnimation{ nullptr };
        winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeBackwardAnimation{ nullptr };

        WallpaperManager m_wallpaperManager;
        CombinedWallpaper m_combinedWallpaper;

        void createEffects(ID2D1DeviceContext* d2dContext);
        void createBrush(ID2D1DeviceContext* d2dContext);
        
        void updateBrushOffset();
        void updateBrushOffset(int windowX, int windowY);

        void createAnimation();
        UINT m_dpi{ 96 };
        winrt::Windows::UI::Composition::CompositionBrush makeBrush();

        void draw();

        static LRESULT CALLBACK subclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop, implementation::TenMicaBackdrop>
    {
    };
}
