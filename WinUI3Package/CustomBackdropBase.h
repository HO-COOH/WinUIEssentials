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
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_enableWhenInactiveProperty;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CustomBackdropBase : CustomBackdropBaseT<CustomBackdropBase, implementation::CustomBackdropBase>
    {
    };
}
