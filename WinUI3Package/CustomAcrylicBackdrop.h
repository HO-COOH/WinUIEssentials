#pragma once

#include "CustomAcrylicBackdrop.g.h"
#include "include/EnsureDependencyProperty.hpp"
#include "CustomBackdropBase.h"
#include "OverrideChecker.h"
#include "BackdropWindowActiveStateWorkaroundHandler.hpp"
#include "CustomBackdropImplBase.hpp"
namespace winrt::WinUI3Package::implementation
{
    struct CustomAcrylicBackdrop :
        CustomAcrylicBackdropT<CustomAcrylicBackdrop, CustomBackdropBase>,
        EnsureDependencyProperty<CustomAcrylicBackdrop>,
        CustomBackdropImplBase<CustomAcrylicBackdrop, 100>
    {
        friend class CustomBackdropImplBase<CustomAcrylicBackdrop, 100>;

        static void EnsureDependencyProperties();
        CustomAcrylicBackdrop() = default;

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        ) override;

        void OnTargetDisconnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget
        ) override;

        winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind Kind();
        void Kind(winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicKind value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty KindProperty();

        winrt::Microsoft::UI::Xaml::ElementTheme RequestedTheme();
        void RequestedTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);
        static winrt::Microsoft::UI::Xaml::DependencyProperty RequestedThemeProperty();

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
        winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController m_controller{ nullptr };

        OverrideChecker m_overrideChecker;



        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_kindProperty = nullptr;
        static inline winrt::Microsoft::UI::Xaml::DependencyProperty s_requestedThemeProperty = nullptr;
        static void onKindPropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& backdrop,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        void makeController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target);
        void disposeController();

        static void onThemePropertyChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& backdrop,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& themePropertyArg
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CustomAcrylicBackdrop : CustomAcrylicBackdropT<CustomAcrylicBackdrop, implementation::CustomAcrylicBackdrop>
    {
    };
}
