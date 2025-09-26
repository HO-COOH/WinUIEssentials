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
		auto comboBoxLoadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::ComboBox::Loaded_revoker>();
		*comboBoxLoadedRevoker = comboBox.Loaded(winrt::auto_revoke, [comboBoxLoadedRevoker](auto&& comboBoxRef, auto&&) 
		{
			auto comboBox = comboBoxRef.as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>();
			auto popup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(
				comboBox, 
				L"Popup"
			);

			comboBoxLoadedRevoker->revoke();
			auto border = popup.FindName(L"PopupBorder").as<winrt::Microsoft::UI::Xaml::Controls::Border>();

			auto borderLoadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::Border::Loaded_revoker>();
			*borderLoadedRevoker = border.Loaded(winrt::auto_revoke, [comboBoxRef = winrt::make_weak(comboBox), borderLoadedRevoker](auto const& borderRef, auto&&)
			{
				borderLoadedRevoker->revoke();
				auto border = borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>();
			
				winrt::WinUI3Package::AcrylicVisual visual;
				visual.CornerRadius(border.CornerRadius());
				VisualTreeHelper::FindVisualChildByType<winrt::Microsoft::UI::Xaml::Controls::Grid>(border).Children().InsertAt(0, visual);

				if (auto comboBox = comboBoxRef.get(); !comboBox.IsEditable())
				{
					comboBox.IsDropDownOpen(true);
				}
			});
		});
	}
}
