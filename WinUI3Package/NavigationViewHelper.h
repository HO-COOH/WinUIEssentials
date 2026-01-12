#pragma once

#include "NavigationViewHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct NavigationViewHelper : NavigationViewHelperT<NavigationViewHelper>
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView,
            bool value
        );

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;
        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

        static void modifyNavigationViewItems(
            winrt::Microsoft::UI::Xaml::Controls::NavigationView const& navigationView, 
            winrt::Microsoft::UI::Xaml::Style const& newStyle
        );

        static void onFlyoutOpened(
            winrt::Windows::Foundation::IInspectable const& sender, 
            winrt::Windows::Foundation::IInspectable const&
        );

        static winrt::Microsoft::UI::Xaml::Style getStyle();
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct NavigationViewHelper : NavigationViewHelperT<NavigationViewHelper, implementation::NavigationViewHelper>
    {
    };
}
