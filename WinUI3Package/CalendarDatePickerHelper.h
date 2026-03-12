#pragma once

#include "CalendarDatePickerHelper.g.h"
#include "include/EnsureDependencyProperty.hpp"

namespace winrt::WinUI3Package::implementation
{
    struct CalendarDatePickerHelper : CalendarDatePickerHelperT<CalendarDatePickerHelper>, EnsureDependencyProperty<CalendarDatePickerHelper>
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker const& picker);
        static void SetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker const& picker, bool value);

    private:

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct CalendarDatePickerHelper : CalendarDatePickerHelperT<CalendarDatePickerHelper, implementation::CalendarDatePickerHelper>
    {
    };
}
