#pragma once

#include "DatePickerHelper.g.h"

namespace winrt::WinUI3Package::implementation
{
    struct DatePickerHelper : DatePickerHelperT<DatePickerHelper>
    {
        static winrt::Microsoft::UI::Xaml::DependencyProperty AcrylicWorkaroundProperty();
        static bool GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::DatePicker const& datePicker);
        static void SetAcrylicWorkaround(
            winrt::Microsoft::UI::Xaml::Controls::DatePicker const& datePicker,
            bool value
        );

    private:
        static winrt::Microsoft::UI::Xaml::DependencyProperty s_acrylicWorkaroundProperty;

        static bool modifyDatePickerFlyoutPresenter(
            winrt::Microsoft::UI::Xaml::Controls::DatePickerFlyoutPresenter const& presenter
        );

        static void acrylicWorkaroundChanged(
            winrt::Microsoft::UI::Xaml::DependencyObject const& object,
            winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
        );
    };
}

namespace winrt::WinUI3Package::factory_implementation
{
    struct DatePickerHelper : DatePickerHelperT<DatePickerHelper, implementation::DatePickerHelper>
    {
    };
}
