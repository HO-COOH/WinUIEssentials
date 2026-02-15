#pragma once

#include "CustomAcrylicBackdrop.g.h"
#include "CustomBackdropBase.h"
#include "OverrideChecker.h"
#include "BackdropWindowActiveStateWorkaroundHandler.hpp"
namespace winrt::WinUI3Package::implementation
{
    struct CustomAcrylicBackdrop : CustomAcrylicBackdropT<CustomAcrylicBackdrop, CustomBackdropBase>
    {
        CustomAcrylicBackdrop() = default;

        void OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget);

        void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, 
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot);

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
        HWND m_hwnd{};
        winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configuration{ nullptr };
        winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController m_controller{ nullptr };

        WNDPROC m_oldProc{};
        LONG_PTR m_oldUserData{};
        winrt::Microsoft::UI::Xaml::XamlRoot::Changed_revoker m_xamlRootChangedRevoker;

        OverrideChecker m_overrideChecker;



        static winrt::Microsoft::UI::Xaml::DependencyProperty s_kindProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_requestedThemeProperty;
        static winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropTheme toBackdropTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);

        //workaround for m_configuration not able to send inactive state when switching to other window created in the same app package
        constexpr static UINT_PTR subclassId = 100;
        friend class BackdropWindowActiveStateWorkaroundHandler<CustomAcrylicBackdrop, subclassId>;

        void changeTheme(winrt::Microsoft::UI::Xaml::ElementTheme theme);
        void makeAcrylicController(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target);
        void disposeAcrylicController();

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
