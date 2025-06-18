#include "pch.h"
#include "ComboBoxHelper.h"
#if __has_include("ComboBoxHelper.g.cpp")
#include "ComboBoxHelper.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
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
		comboBox.LayoutUpdated([comboxBoxRef = winrt::make_weak(comboBox), called = false](auto&&...) mutable 
		{
			if (called) return;

			auto popup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(
				comboxBoxRef.get().as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>(), 
				L"Popup"
			);
			if (!popup) return;

			called = true;
			auto border = popup.FindName(L"PopupBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>();
			border.SizeChanged([called = false, visualRef = winrt::weak_ref<winrt::WinUI3Package::AcrylicVisual>{}](auto const& borderRef, winrt::Microsoft::UI::Xaml::SizeChangedEventArgs const& args) mutable
			{
				if (called)
				{
					if (auto visual = visualRef.get())
						visual.CornerRadius(borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>().CornerRadius());
					return;
				}

				// The border might still be not fully loaded, which might return a size of 0, rule out this situation here
				auto border = borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>();
				if (auto const newSize = args.NewSize(); newSize.Width == 0 || newSize.Height == 0)
					return;
				called = true;
				auto originalChild = border.Child();

				winrt::Microsoft::UI::Xaml::Controls::Grid scrollGrid;
				border.Child(scrollGrid);

				winrt::WinUI3Package::AcrylicVisual visual;
				visual.CornerRadius(border.CornerRadius());
				scrollGrid.Children().ReplaceAll({ visual, originalChild });
				visualRef = visual;
			});
		});
	}
}
