#pragma once

#include "NumberBoxHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct NumberBoxHelper
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& numberBox);
        static void SetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& numberBox, bool value);

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
    struct NumberBoxHelper : NumberBoxHelperT<NumberBoxHelper, implementation::NumberBoxHelper>
    {
    };
}
