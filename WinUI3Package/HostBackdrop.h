#pragma once

#include "HostBackdrop.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct HostBackdrop : HostBackdropT<HostBackdrop>, EnsureDependencyProperty<HostBackdrop>
    {
        static void EnsureDependencyProperties();

        void OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot);
        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);

        float BlurAmount();
        void BlurAmount(float value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty BlurAmountProperty();
    private:
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_blurAmountProperty{ nullptr };

        winrt::Windows::UI::Composition::CompositionEffectBrush m_effectBrush{ nullptr };

        static void onBlurAmountChanged(
            winrt::WinUINamespace::UI::Xaml::DependencyObject const& d,
            winrt::WinUINamespace::UI::Xaml::DependencyPropertyChangedEventArgs const& e
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct HostBackdrop : HostBackdropT<HostBackdrop, implementation::HostBackdrop>
    {
    };
}
