#include "pch.h"
#include "TimePickerHelper.h"
#if __has_include("TimePickerHelper.g.cpp")
#include "TimePickerHelper.g.cpp"
#endif
#include <include/VisualTreeHelper.hpp>
#include "AcrylicVisualWithBoundedCornerRadius.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty TimePickerHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&TimePickerHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty TimePickerHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool TimePickerHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::TimePicker const& timePicker)
	{
		return winrt::unbox_value<bool>(timePicker.GetValue(AcrylicWorkaroundProperty()));
	}

	void TimePickerHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::TimePicker const& timePicker,
		bool value
	)
	{
		timePicker.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}
	
	bool TimePickerHelper::modifyTimePickerFlyoutPresenter(winrt::Microsoft::UI::Xaml::Controls::TimePickerFlyoutPresenter const& presenter)
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

	void TimePickerHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
	)
	{
		auto value = winrt::unbox_value<bool>(arg.NewValue());
		if (!value)
			return;

		auto timePicker = object.as<winrt::Microsoft::UI::Xaml::Controls::TimePicker>();
		timePicker.Loaded([](auto const& timePickerRef, auto&&) {
			auto timePicker = timePickerRef.as<winrt::Microsoft::UI::Xaml::Controls::TimePicker>();

			if (auto flyoutButton = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Button>(timePicker, L"FlyoutButton"))
			{
				flyoutButton.Click([](auto&& flyoutButtonRef, auto&&...)
				{
					auto flyoutButton = flyoutButtonRef.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
					flyoutButton.DispatcherQueue().TryEnqueue([xamlRoot = flyoutButton.XamlRoot()]
					{
						for (auto popup : winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetOpenPopupsForXamlRoot(xamlRoot))
						{
							if (auto presenter = popup.Child().try_as<winrt::Microsoft::UI::Xaml::Controls::TimePickerFlyoutPresenter>())
							{
								if (winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(presenter) > 0)
									modifyTimePickerFlyoutPresenter(presenter);
								else
								{
									// If the visual tree is not ready, wait for LayoutUpdated
									auto layoutUpdatedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::FrameworkElement::LayoutUpdated_revoker>();
									*layoutUpdatedRevoker = presenter.LayoutUpdated(winrt::auto_revoke, [layoutUpdatedRevoker, presenter = winrt::make_weak(presenter)](auto&&...)
									{
										if (auto strongPresenter = presenter.get())
										{
											if (modifyTimePickerFlyoutPresenter(strongPresenter))
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
