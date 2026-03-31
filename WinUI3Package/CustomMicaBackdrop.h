#pragma once

#include "CustomMicaBackdrop.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "OverrideChecker.h"
#include "BackdropWindowActiveStateWorkaroundHandler.hpp"
#include "CustomBackdropBase.h"
#include "CustomBackdropImplBase.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct CustomMicaBackdrop : 
        CustomMicaBackdropT<CustomMicaBackdrop, CustomBackdropBase>, 
        EnsureDependencyProperty<CustomMicaBackdrop>, 
        CustomBackdropImplBase<CustomMicaBackdrop, 101>
    {
		friend class CustomBackdropImplBase<CustomMicaBackdrop, 101>;

        static void EnsureDependencyProperties();
        CustomMicaBackdrop() = default;

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        ) override;

        void OnTargetDisconnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget
        ) override;

        winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind Kind();
        void Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::MicaKind value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty KindProperty();

        #pragma region VirtualFunctions
        void OnFallbackColorChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        void OnLuminosityOpacityChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        void OnTintColorChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        void OnTintOpacityChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        #pragma endregion
    private:
        winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController m_controller{ nullptr };

        static void onKindPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& sender,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );



        OverrideChecker m_overrideChecker;

        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_kindProperty = nullptr;

        void makeController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target);
        void disposeController();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CustomMicaBackdrop : CustomMicaBackdropT<CustomMicaBackdrop, implementation::CustomMicaBackdrop>
    {
    };
}
