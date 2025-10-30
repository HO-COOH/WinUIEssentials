#include "pch.h"
#include "ToolTipHelper.h"
#if __has_include("ToolTipHelper.g.cpp")
#include "ToolTipHelper.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ToolTipHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, 
				&ToolTipHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ToolTipHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool ToolTipHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip)
	{
		return winrt::unbox_value<bool>(toolTip.GetValue(AcrylicWorkaroundProperty()));
	}

	void ToolTipHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::ToolTip const& toolTip,
		bool value
	)
	{
		toolTip.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	void ToolTipHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto tooltip = object.as<winrt::Microsoft::UI::Xaml::Controls::ToolTip>();
		tooltip.Loading([](auto&& sender, auto&&) {
			winrt::WinUI3Package::CustomAcrylicBackdrop backdrop;
			auto tooltip = sender
				.as<winrt::Microsoft::UI::Xaml::Controls::ToolTip>();
			tooltip.Parent()
				.as<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>()
				.SystemBackdrop(
					backdrop
				);
			tooltip.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{
				winrt::Windows::UI::Colors::Transparent()
			});

			backdrop.RequestedTheme(tooltip.ActualTheme());
		});
	}
}
