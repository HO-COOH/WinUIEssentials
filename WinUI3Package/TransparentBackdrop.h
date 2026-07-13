#pragma once
#include "TransparentBackdrop.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct TransparentBackdrop : TransparentBackdropT<TransparentBackdrop>
    {

        void OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot);
        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);

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
