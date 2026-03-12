#pragma once

#include "CommandBarHelper.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct CommandBarHelper : CommandBarHelperT<CommandBarHelper>, EnsureDependencyProperty<CommandBarHelper>
    {
		static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
		static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::CommandBar const& commandBar);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::CommandBar const& commandBar,
            bool value
        );

    private:

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CommandBarHelper : CommandBarHelperT<CommandBarHelper, implementation::CommandBarHelper>
    {
    };
}
