#include "pch.h"
#include "DatePickerHelper.h"
#if __has_include("DatePickerHelper.g.cpp")
#include "DatePickerHelper.g.cpp"
#endif
#include <include/VisualTreeHelper.hpp>
#include "AcrylicVisualWithBoundedCornerRadius.h"
#include <include/VisualTreeHelper.hpp>

namespace winrt::WinUI3Package::implementation
{
    winrt::Microsoft::UI::Xaml::DependencyProperty DatePickerHelper::s_acrylicWorkaroundProperty =
        winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
            L"AcrylicWorkaround",
            winrt::xaml_typename<bool>(),
            winrt::xaml_typename<class_type>(),
            winrt::Microsoft::UI::Xaml::PropertyMetadata{
                nullptr,
                &DatePickerHelper::acrylicWorkaroundChanged
            }
        );

    winrt::Microsoft::UI::Xaml::DependencyProperty DatePickerHelper::AcrylicWorkaroundProperty()
    {
        return s_acrylicWorkaroundProperty;
    }

    bool DatePickerHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::DatePicker const& datePicker)
    {
        return winrt::unbox_value<bool>(datePicker.GetValue(AcrylicWorkaroundProperty()));
    }

    void DatePickerHelper::SetAcrylicWorkaround(
        winrt::Microsoft::UI::Xaml::Controls::DatePicker const& datePicker,
        bool value
    )
    {
        datePicker.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
    }

    bool DatePickerHelper::modifyDatePickerFlyoutPresenter(winrt::Microsoft::UI::Xaml::Controls::DatePickerFlyoutPresenter const& presenter)
    {
        auto border = VisualTreeHelper::FindVisualChildByType<winrt::Microsoft::UI::Xaml::Controls::Border>(presenter);
        if (!border)
            return false;

        auto oldChild = border.Child();
        border.Child(nullptr);

        winrt::Microsoft::UI::Xaml::Controls::Grid newChild;
        newChild.Children().ReplaceAll({ AcrylicVisualWithBoundedCornerRadius{border}, oldChild });

        border.Child(newChild);

        presenter.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });
        border.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });
        
        return true;
    }

    void DatePickerHelper::acrylicWorkaroundChanged(
        winrt::Microsoft::UI::Xaml::DependencyObject const& object,
        winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
    )
    {
        auto value = winrt::unbox_value<bool>(arg.NewValue());
        if (!value)
            return;
        
        auto datePicker = object.as<winrt::Microsoft::UI::Xaml::Controls::DatePicker>();
        datePicker.Loaded([](auto const& datePickerRef, auto&&) {
            auto datePicker = datePickerRef.as<winrt::Microsoft::UI::Xaml::Controls::DatePicker>();
            
            if (auto flyoutButton = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Button>(datePicker, L"FlyoutButton"))
            {
                //Do not revoke the click handler, because it seems that the flyout is reloaded every time
                flyoutButton.Click([](auto&& flyoutButtonRef, auto&&...)
                {
                    auto flyoutButton = flyoutButtonRef.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
                    flyoutButton.DispatcherQueue().TryEnqueue([xamlRoot = flyoutButton.XamlRoot()]
                    {
                        for (auto popup : winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetOpenPopupsForXamlRoot(xamlRoot))
                        {
                            if (auto presenter = popup.Child().try_as<winrt::Microsoft::UI::Xaml::Controls::DatePickerFlyoutPresenter>())
                            {
                                if (winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(presenter) > 0)
                                    modifyDatePickerFlyoutPresenter(presenter);
                                else
                                {
                                    // If the visual tree is not ready, wait for LayoutUpdated
                                    auto layoutUpdatedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::FrameworkElement::LayoutUpdated_revoker>();
                                    *layoutUpdatedRevoker = presenter.LayoutUpdated(winrt::auto_revoke, [layoutUpdatedRevoker, presenter = winrt::make_weak(presenter)](auto&&...) 
                                    {
                                        if (auto strongPresenter = presenter.get())
                                        {
                                            if (modifyDatePickerFlyoutPresenter(strongPresenter))
                                                layoutUpdatedRevoker->revoke();
                                        }
                                    });
                                }
                                return;
                            }
                        }
                    });
                });
            }
        });
    }
}
