#include "pch.h"
#include "ColorPickerHelper.h"
#if __has_include("ColorPickerHelper.g.cpp")
#include "ColorPickerHelper.g.cpp"
#endif
#include <VisualTreeHelper.hpp>

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ColorPickerHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::WinUI3Package::ColorPickerHelper>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&ColorPickerHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ColorPickerHelper::s_toolTipDismissWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"ToolTipDismissWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::WinUI3Package::ColorPickerHelper>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&ColorPickerHelper::toolTipDismissWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ColorPickerHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool ColorPickerHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& colorPicker)
	{
		return winrt::unbox_value<bool>(colorPicker.GetValue(s_acrylicWorkaroundProperty));
	}

	void ColorPickerHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& colorPicker,
		bool value
	)
	{
		colorPicker.SetValue(s_acrylicWorkaroundProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty ColorPickerHelper::ToolTipDismissWorkaroundProperty()
	{
		return s_toolTipDismissWorkaroundProperty;
	}

	bool ColorPickerHelper::GetToolTipDismissWorkaround(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& colorPicker)
	{
		return winrt::unbox_value<bool>(colorPicker.GetValue(s_toolTipDismissWorkaroundProperty));
	}

	void ColorPickerHelper::SetToolTipDismissWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& colorPicker,
		bool value
	)
	{
		colorPicker.SetValue(s_toolTipDismissWorkaroundProperty, winrt::box_value(value));
	}

	void ColorPickerHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;
		auto colorPicker = object.as<winrt::Microsoft::UI::Xaml::Controls::ColorPicker>();
		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::ColorPicker::Loaded_revoker>();
		*loadedRevoker = colorPicker.Loaded(winrt::auto_revoke, [loadedRevoker](auto const& sender, auto const& args)
		{
			auto colorPicker = sender.as<winrt::Microsoft::UI::Xaml::Controls::ColorPicker>();
			colorPicker.ApplyTemplate();

			if (auto colorSpectrum = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::ColorSpectrum>(colorPicker, L"ColorSpectrum"))
				applyAcrylic(colorSpectrum);

			if (auto ThirdDimensionSlider = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Slider>(colorPicker, L"ThirdDimensionSlider"))
				applyAcrylic(ThirdDimensionSlider);

			if (auto AlphaSlider = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Slider>(colorPicker, L"AlphaSlider"))
				applyAcrylic(AlphaSlider);

			if (auto ColorRepresentationComboBox = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::ComboBox>(colorPicker, L"ColorRepresentationComboBox"))
				winrt::WinUI3Package::ComboBoxHelper::SetAcrylicWorkaround(ColorRepresentationComboBox, true);

			loadedRevoker->revoke();
		});
	}

	void ColorPickerHelper::toolTipDismissWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const toolTipDismissWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!toolTipDismissWorkaround)
			return;

		auto colorPicker = object.as<winrt::Microsoft::UI::Xaml::Controls::ColorPicker>();
		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::ColorPicker::Loaded_revoker>();
		*loadedRevoker = colorPicker.Loaded(winrt::auto_revoke, [loadedRevoker](auto const& sender, auto const& args)
		{
			auto colorPicker = sender.as<winrt::Microsoft::UI::Xaml::Controls::ColorPicker>();
			colorPicker.ApplyTemplate();
			
			auto colorSpectrum = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::ColorSpectrum>(colorPicker, L"ColorSpectrum");
			colorSpectrum.ApplyTemplate();
			
			auto ellipse = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Shapes::Ellipse>(colorSpectrum, L"SelectionEllipse");
			auto tooltipRef = winrt::Microsoft::UI::Xaml::Controls::ToolTipService::GetToolTip(ellipse);
			if (!tooltipRef)
				return;

			if (auto tooltip = tooltipRef.try_as<winrt::Microsoft::UI::Xaml::Controls::ToolTip>())
			{
				auto isToolTipOpen = [weakToolTip = winrt::make_weak(tooltip)](bool isOpen)
				{
					if (auto tooltip = weakToolTip.get())
						tooltip.IsOpen(isOpen);
				};

				auto inputTarget = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Canvas>(colorSpectrum, L"InputTarget");
				inputTarget.AddHandler(
					winrt::Microsoft::UI::Xaml::UIElement::PointerPressedEvent(),
					winrt::box_value(winrt::Microsoft::UI::Xaml::Input::PointerEventHandler{ [isToolTipOpen](auto&&...) {isToolTipOpen(true);} }),
					true
				);

				winrt::Microsoft::UI::Xaml::Input::PointerEventHandler close{ [isToolTipOpen](auto&&...) {isToolTipOpen(false);} };
				inputTarget.AddHandler(
					winrt::Microsoft::UI::Xaml::UIElement::PointerReleasedEvent(),
					winrt::box_value(close),
					true
				);
				inputTarget.AddHandler(
					winrt::Microsoft::UI::Xaml::UIElement::PointerCaptureLostEvent(),
					winrt::box_value(close),
					true
				);
			}
		});
	}

	void ColorPickerHelper::applyAcrylic(winrt::Microsoft::UI::Xaml::Controls::Primitives::ColorSpectrum const& colorSpectrum)
	{
		colorSpectrum.ApplyTemplate();
		auto ellipse = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Shapes::Ellipse>(colorSpectrum, L"SelectionEllipse");
		applyAcrylicToOwnedToolTip(ellipse);
	}

	void ColorPickerHelper::applyAcrylic(winrt::Microsoft::UI::Xaml::Controls::Slider const& slider)
	{
		slider.ApplyTemplate();
		applyAcrylicToOwnedToolTip(VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Thumb>(slider, L"HorizontalThumb"));
		applyAcrylicToOwnedToolTip(VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Thumb>(slider, L"VerticalThumb"));
	}

	void ColorPickerHelper::applyAcrylicToOwnedToolTip(winrt::Microsoft::UI::Xaml::DependencyObject const& tooltipOwner)
	{
		if (!tooltipOwner)
			return;

		auto tooltipRef = winrt::Microsoft::UI::Xaml::Controls::ToolTipService::GetToolTip(tooltipOwner);
		if (!tooltipRef)
			return;

		if (auto tooltip = tooltipRef.try_as<winrt::Microsoft::UI::Xaml::Controls::ToolTip>())
			winrt::WinUI3Package::ToolTipHelper::SetAcrylicWorkaround(tooltip,true);
	}
}
