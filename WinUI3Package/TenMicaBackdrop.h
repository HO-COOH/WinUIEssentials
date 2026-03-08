#pragma once

#include "TenMicaBackdrop.g.h"

#include <winrt/Windows.UI.Composition.h>
#include "CustomBackdropBase.h"
#include "TenMicaEffectFactory.h"
#include "TenMicaWindowSubProc.hpp"
#include "TenMicaRegistryWatcher.h"
#include "EnsureSystemDispatcherQueueController.hpp"
#include <optional>
#include <memory>

namespace winrt::WinUI3Package::implementation
{
    struct TenMicaBackdrop : TenMicaBackdropT<TenMicaBackdrop, CustomBackdropBase>, TenMicaWindowSubProc<TenMicaBackdrop>, EnsureSystemDispatcherQueueController<TenMicaBackdrop>
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
        void onDisplayChanged();
    private:
        TenMicaEffect& getEffect();

        winrt::weak_ref<winrt::Microsoft::UI::Xaml::FrameworkElement> m_bindThemeTo;
        winrt::Microsoft::UI::Xaml::FrameworkElement::ActualThemeChanged_revoker m_bindThemeRevoker;
        winrt::Microsoft::UI::Dispatching::DispatcherQueue m_queue = winrt::Microsoft::UI::Dispatching::DispatcherQueue::GetForCurrentThread();
        std::optional<TenMicaRegistryWatcher> m_registryWatcher;
        std::optional<TenMicaEffect> m_effect;
        std::shared_ptr<TenMicaEffectFactory> m_factory{ TenMicaEffectFactory::GetFactory() };
        void getVirtualScreenXY();
        void onDeviceReset();
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
