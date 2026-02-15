#pragma once

#include "CustomMicaBackdrop.g.h"
#include "OverrideChecker.h"
#include "BackdropWindowActiveStateWorkaroundHandler.hpp"
#include "CustomBackdropBase.h"

namespace winrt::WinUI3Package::implementation
{
    struct CustomMicaBackdrop : CustomMicaBackdropT<CustomMicaBackdrop, CustomBackdropBase>
    {
        CustomMicaBackdrop() = default;

        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, 
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        );

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
        HWND m_hwnd{};
        winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configuration{ nullptr };
        winrt::Microsoft::UI::Composition::SystemBackdrops::MicaController m_controller{ nullptr };

        WNDPROC m_oldProc{};
        LONG_PTR m_oldUserData{};
        winrt::Microsoft::UI::Xaml::XamlRoot::Changed_revoker m_xamlRootChangedRevoker;

        OverrideChecker m_overrideChecker;

        static winrt::Microsoft::UI::Xaml::DependencyProperty s_kindProperty;

        static winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme toBackdropTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);

        //workaround for m_configuration not able to send inactive state when switching to other window created in the same app package
        constexpr static UINT_PTR subclassId = 101;
        friend class BackdropWindowActiveStateWorkaroundHandler<CustomMicaBackdrop, subclassId>;

        void changeTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);
        void makeMicaController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target);
        void disposeMicaController();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CustomMicaBackdrop : CustomMicaBackdropT<CustomMicaBackdrop, implementation::CustomMicaBackdrop>
    {
    };
}
