#pragma once

#include "TenMicaBackdrop.g.h"
#include <d2d1_1.h>
#include <winrt/Windows.UI.Composition.h>
#include "WallpaperManager.h"
#include "CombinedWallpaper.h"
#include "CustomBackdropBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop, CustomBackdropBase>
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

        // Light and dark theme surfaces
        winrt::Windows::UI::Composition::CompositionDrawingSurface m_lightSurface{ nullptr };
        winrt::Windows::UI::Composition::CompositionDrawingSurface m_darkSurface{ nullptr };
        winrt::Windows::UI::Composition::CompositionSurfaceBrush m_lightBrush{ nullptr };
        winrt::Windows::UI::Composition::CompositionSurfaceBrush m_darkBrush{ nullptr };

        winrt::Windows::UI::Composition::CompositionEffectBrush m_themeCrossFadeBrush{ nullptr };
        winrt::Windows::UI::Composition::CompositionEffectBrush crossFadeBrush{ nullptr };
        winrt::Windows::UI::Composition::CompositionColorBrush m_inactiveBrush{ nullptr };
        winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeForwardAnimation{ nullptr };
        winrt::Windows::UI::Composition::ScalarKeyFrameAnimation m_crossFadeBackwardAnimation{ nullptr };

        WallpaperManager m_wallpaperManager;
        CombinedWallpaper m_combinedWallpaper;

        void createEffects(ID2D1DeviceContext* d2dContext);
        void createBrush(bool isLightMode);
        
        void updateBrushOffset();
        void updateBrushOffset(int windowX, int windowY);

        void createAnimation();
        void onThemeChanged(bool isLightTheme);
        int m_virtualScreenX{ 0 };
        int m_virtualScreenY{ 0 };
        winrt::Windows::UI::Composition::CompositionBrush makeBrush();

        void draw(winrt::Windows::UI::Composition::CompositionDrawingSurface const& surface, bool isLightMode);

        static LRESULT CALLBACK subclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop, implementation::TenMicaBackdrop>
    {
    };
}
