#pragma once
#include "MicaBackdropWithFallback.g.h"
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>

namespace winrt::WinUI3Package::implementation
{
    struct MicaBackdropWithFallback : MicaBackdropWithFallbackT<MicaBackdropWithFallback>
    {
        MicaBackdropWithFallback() = default;
        MicaBackdropWithFallback(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& fallback);

        winrt::Microsoft::UI::Xaml::Media::SystemBackdrop Fallback();
        void Fallback(winrt::Microsoft::UI::Xaml::Media::SystemBackdrop const& value);

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, 
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        );

        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);

        void OnDefaultSystemBackdropConfigurationChanged(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        );
    private:
        winrt::Microsoft::UI::Xaml::Media::SystemBackdrop m_fallback{ nullptr };
        bool const m_isMicaSupported = winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController::IsSupported();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct MicaBackdropWithFallback : MicaBackdropWithFallbackT<MicaBackdropWithFallback, implementation::MicaBackdropWithFallback>
    {
    };
}
