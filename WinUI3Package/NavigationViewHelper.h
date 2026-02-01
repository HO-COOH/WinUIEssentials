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

        static winrt::Microsoft::UI::Xaml::DependencyProperty ClipToBoundsProperty();
        static bool GetClipToBounds(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& element);
        static void SetClipToBounds(winrt::Microsoft::UI::Xaml::Controls::NavigationView const& element, bool value);
    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_clipToBoundsProperty;

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

        static void clipToBoundsChanged(
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

        static winrt::Microsoft::UI::Xaml::Style getStyle(winrt::Microsoft::UI::Xaml::Style const& defaultNavigationViewFlyoutStyle);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct NavigationViewHelper : NavigationViewHelperT<NavigationViewHelper, implementation::NavigationViewHelper>
    {
    };
}
