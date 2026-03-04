#include "pch.h"
#include "SliderHelper.h"
#if __has_include("SliderHelper.g.cpp")
#include "SliderHelper.g.cpp"
#endif

#include "VisualTreeHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty SliderHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&SliderHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty SliderHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool SliderHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::Slider const& slider)
	{
		return winrt::unbox_value<bool>(slider.GetValue(AcrylicWorkaroundProperty()));
	}

	void SliderHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::Slider const& slider,
		bool value
	)
	{
		slider.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}


	void SliderHelper::applyThumbAcrylic(winrt::Microsoft::UI::Xaml::Controls::Primitives::Thumb const& thumb)
	{

		auto spToolTip = winrt::Microsoft::UI::Xaml::Controls::ToolTipService::GetToolTip(thumb);

		if (!spToolTip) 
			return;

		auto tooltip = spToolTip.try_as<winrt::Microsoft::UI::Xaml::Controls::ToolTip>();

		if (!tooltip) 
			return;

		winrt::WinUI3Package::ToolTipHelper::SetAcrylicWorkaround(tooltip, true);

	}


	void SliderHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto slider = object.as<winrt::Microsoft::UI::Xaml::Controls::Slider>();
		if (!slider) return;

		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::FrameworkElement::Loaded_revoker>();
		*loadedRevoker = slider.Loaded(winrt::auto_revoke, [loadedRevoker](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
		{
			auto slider = sender.as<winrt::Microsoft::UI::Xaml::Controls::Slider>();

			auto horizontalThumb = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Thumb>(slider, L"HorizontalThumb");

			if (horizontalThumb) 
				applyThumbAcrylic(horizontalThumb);

			auto verticalThumb = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Thumb>(slider, L"VerticalThumb");

			if (verticalThumb) 
				applyThumbAcrylic(verticalThumb);

			loadedRevoker->revoke();
		});
	}
}
