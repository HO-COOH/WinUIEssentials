#pragma once

#include "ToolTipHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct ToolTipHelper : ToolTipHelperT<ToolTipHelper>
    {
        ToolTipHelper() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ToolTip const& comboBox);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::ToolTip const& comboBox,
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
    struct ToolTipHelper : ToolTipHelperT<ToolTipHelper, implementation::ToolTipHelper>
    {
    };
}
