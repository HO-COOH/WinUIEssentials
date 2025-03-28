#pragma once

#include "ComboBoxHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ComboBoxHelper : ComboBoxHelperT<ComboBoxHelper>
    {
        ComboBoxHelper() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox,
            bool value
        );

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

        static winrt::Microsoft::UI::Composition::SystemBackdrops::DesktopAcrylicController acrylicController;
        static winrt::Microsoft::UI::Composition::SystemBackdrops::SystemBackdropConfiguration m_configuration;

        constexpr static float ComboBoxCornerRadius = 8.f;
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ComboBoxHelper : ComboBoxHelperT<ComboBoxHelper, implementation::ComboBoxHelper>
    {
    };
}
