#pragma once

#include "ComboBoxHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ComboBoxHelper
    {
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
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct ComboBoxHelper : ComboBoxHelperT<ComboBoxHelper, implementation::ComboBoxHelper>
    {
    };
}
