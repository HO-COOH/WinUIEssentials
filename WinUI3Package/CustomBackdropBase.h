#pragma once

#include "CustomBackdropBase.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct CustomBackdropBase : CustomBackdropBaseT<CustomBackdropBase>
    {
        CustomBackdropBase() = default;

        bool EnableWhenInactive();
        void EnableWhenInactive(bool value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty EnableWhenInactiveProperty();

        winrt::Windows::UI::Color FallbackColor();
        void FallbackColor(winrt::Windows::UI::Color value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty FallbackColorProperty();

        float LuminosityOpacity();
        void LuminosityOpacity(float value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty LuminosityOpacityProperty();

        winrt::Windows::UI::Color TintColor();
        void TintColor(winrt::Windows::UI::Color value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TintColorProperty();

        float TintOpacity();
        void TintOpacity(float value);
        static winrt::Microsoft::UI::Xaml::DependencyProperty TintOpacityProperty();

        #pragma region VirtualFunctions
        virtual void OnTargetConnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        );
        virtual void OnTargetDisconnected(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget
        );
        virtual void OnDefaultSystemBackdropConfigurationChanged(
            winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& target,
            winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot
        );
        virtual void OnFallbackColorChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        virtual void OnLuminosityOpacityChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        virtual void OnTintColorChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        virtual void OnTintOpacityChanged(
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        #pragma endregion
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_enableWhenInactiveProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_fallbackColorProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_luminosityOpacityProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_tintColorProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_tintOpacityProperty;

        static void onFallbackColorChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        static void onLuminosityOpacityChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        static void onTintColorChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
        static void onTintOpacityChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& d,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& args
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CustomBackdropBase : CustomBackdropBaseT<CustomBackdropBase, implementation::CustomBackdropBase>
    {
    };
}
