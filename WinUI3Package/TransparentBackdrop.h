#pragma once

#include "TransparentBackdrop.g.h"
#include "WindowEx.h"

namespace winrt::WinUI3Package::implementation
{
    struct TransparentBackdrop : TransparentBackdropT<TransparentBackdrop>
    {
        TransparentBackdrop() = default;

        void OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot xamlRoot);
        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop connectedTarget);

    private:
        static void configureDwm(HWND hwnd);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TransparentBackdrop : TransparentBackdropT<TransparentBackdrop, implementation::TransparentBackdrop>
    {
    };
}
