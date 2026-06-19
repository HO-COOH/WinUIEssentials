#pragma once

#include "HostBackdrop.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct HostBackdrop : HostBackdropT<HostBackdrop>
    {
        HostBackdrop() = default;

        void OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot);
        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct HostBackdrop : HostBackdropT<HostBackdrop, implementation::HostBackdrop>
    {
    };
}
