#include "pch.h"
#include "ComboBoxHelper.h"
#if __has_include("ComboBoxHelper.g.cpp")
#include "ComboBoxHelper.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Composition.SystemBackdrops.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Hosting.h>
#include <winrt/Microsoft.UI.Content.h>
#include <unordered_map>
#include "AcrylicVisual.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty ComboBoxHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr, 
				&ComboBoxHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty ComboBoxHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool ComboBoxHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox)
	{
		return winrt::unbox_value<bool>(comboBox.GetValue(AcrylicWorkaroundProperty()));
	}

	void ComboBoxHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::ComboBox const& comboBox,
		bool value
	)
	{
		comboBox.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	void ComboBoxHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object, 
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto comboBox = object.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
		comboBox.Loaded([](winrt::Windows::Foundation::IInspectable const& comboBoxRef, auto&&...) {
			auto comboBox = comboBoxRef.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
			auto popup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(comboBox, L"Popup");
			if (!popup) return;

			popup.Opened(
				[
					border = popup.FindName(L"PopupBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>(), 
					comboBoxWeak = winrt::make_weak(comboBox), 
					called = false
				](auto&...) mutable
				{
					//only set the visual once
					if (called)
						return;

					called = true;
					auto size = border.ActualSize();
					border.Translation({ -1.f, 0, 0 });
					auto originalChild = border.Child();
					winrt::Microsoft::UI::Xaml::Controls::Grid scrollGrid;
					scrollGrid.Width(size.x - 1);
					scrollGrid.Height(size.y);
					border.Child(scrollGrid);

					winrt::WinUI3Package::AcrylicVisual visual;
					winrt::get_self<AcrylicVisual>(visual)->ClipOffset.w = -2.f;
	
					visual.CornerRadius({ ComboBoxCornerRadius, ComboBoxCornerRadius, ComboBoxCornerRadius, ComboBoxCornerRadius });
					scrollGrid.Children().ReplaceAll({ visual, originalChild });
				});

			//We need to programmatically open it once, otherwise it will close when we first set its visual, not sure why
			//IsEditable=True is an exception, it will open if we programatically open it
			if (!comboBox.IsEditable())
				comboBox.IsDropDownOpen(true);
		});
	}
}
