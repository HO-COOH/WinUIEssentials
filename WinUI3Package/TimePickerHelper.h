#pragma once

#include "TimePickerHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct TimePickerHelper : TimePickerHelperT<TimePickerHelper>
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::TimePicker const& timePicker);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::TimePicker const& timePicker,
            bool value
        );

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );

        static bool modifyTimePickerFlyoutPresenter(winrt::Microsoft::UI::Xaml::Controls::TimePickerFlyoutPresenter const& presenter);
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct TimePickerHelper : TimePickerHelperT<TimePickerHelper, implementation::TimePickerHelper>
    {
    };
}
