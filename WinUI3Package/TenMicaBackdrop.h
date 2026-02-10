#pragma once

#include "TenMicaBackdrop.g.h"

#include <winrt/Windows.UI.Composition.h>
#include "WallpaperManager.h"
#include "CustomBackdropBase.h"
#include "TenMicaEffectFactory.h"
#include "TenMicaWindowSubProc.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop, CustomBackdropBase>, TenMicaWindowSubProc<TenMicaBackdrop>
    {
        TenMicaBackdrop() = default;

        winrt::Microsoft::UI::Xaml::FrameworkElement BindThemeTo();
        void BindThemeTo(winrt::Microsoft::UI::Xaml::FrameworkElement const value);

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot);

        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);
        
        void updateBrushOffset(int windowX, int windowY);
        void onWindowActivated(bool isActive);
        void onWallpaperChanged();
    private:
        winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement> m_bindThemeTo;
        winrt::Microsoft::UI::Xaml::FrameworkElement::ActualThemeChanged_revoker m_bindThemeRevoker;

        TenMicaEffect m_effect = TenMicaEffectFactory::GetFactory().Get();

        int m_virtualScreenX{};
        int m_virtualScreenY{};
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop, implementation::TenMicaBackdrop>
    {
    };
}
