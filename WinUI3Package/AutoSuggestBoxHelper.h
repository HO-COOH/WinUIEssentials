#pragma once

#include "AutoSuggestBoxHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct AutoSuggestBoxHelper : AutoSuggestBoxHelperT<AutoSuggestBoxHelper>
    {
        AutoSuggestBoxHelper() = default;

        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& autoSuggestBox);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& autoSuggestBox,
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
    struct AutoSuggestBoxHelper : AutoSuggestBoxHelperT<AutoSuggestBoxHelper, implementation::AutoSuggestBoxHelper>
    {
    };
}
