#include "pch.h"
#include "CalendarDatePickerHelper.h"
#if __has_include("CalendarDatePickerHelper.g.cpp")
#include "CalendarDatePickerHelper.g.cpp"
#endif
#include <include/VisualTreeHelper.hpp>
#include "AcrylicVisualWithBoundedCornerRadius.h"
#include "AcrylicVisual.h"

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty CalendarDatePickerHelper::s_acrylicWorkaroundProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"AcrylicWorkaround",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                &CalendarDatePickerHelper::acrylicWorkaroundChanged
            }
        );

    winrt::Microsoft::UI::Xaml::DependencyProperty CalendarDatePickerHelper::AcrylicWorkaroundProperty()
    {
        return s_acrylicWorkaroundProperty;
    }

    bool CalendarDatePickerHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker const& picker)
    {
        return winrt::unbox_value<bool>(picker.GetValue(AcrylicWorkaroundProperty()));
    }

    void CalendarDatePickerHelper::SetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker const& picker, bool value)
    {
        picker.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
    }

    void CalendarDatePickerHelper::acrylicWorkaroundChanged(
        winrt::Microsoft::UI::Xaml::DependencyObject const& object,
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
    )
    {
        auto const value = winrt::unbox_value<bool>(arg.NewValue());
        if (!value)
            return;

        auto picker = object.as<winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker>();
        auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::FrameworkElement::Loaded_revoker>();
        *loadedRevoker = picker.Loaded(winrt::auto_revoke, [loadedRevoker](auto&& sender, auto&&)
        {
            auto picker = sender.as<winrt::Microsoft::UI::Xaml::Controls::CalendarDatePicker>();
            auto root = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Grid>(picker, L"Root");
            auto flyout = winrt::Microsoft::UI::Xaml::Controls::Primitives::FlyoutBase::GetAttachedFlyout(root).as<winrt::Microsoft::UI::Xaml::Controls::Flyout>();
            winrt::Microsoft::UI::Xaml::Media::SolidColorBrush transparentBrush{ winrt::Windows::UI::Colors::Transparent() };
            flyout.FlyoutPresenterStyle().Setters().Append(
                winrt::Microsoft::UI::Xaml::Setter
                {
                    winrt::Microsoft::UI::Xaml::Controls::Control::BackgroundProperty(),
                    transparentBrush
                }
            );
            flyout.SystemBackdrop(Microsoft::UI::Xaml::Media::DesktopAcrylicBackdrop{});
            auto content = flyout.Content().as<winrt::Microsoft::UI::Xaml::Controls::CalendarView>();
            content.Background(transparentBrush);
            loadedRevoker->revoke();
        });
    }
}
