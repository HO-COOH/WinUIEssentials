#include "pch.h"
#include "AutoSuggestBoxHelper.h"
#if __has_include("AutoSuggestBoxHelper.g.cpp")
#include "AutoSuggestBoxHelper.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
#include "AcrylicVisual.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty AutoSuggestBoxHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&AutoSuggestBoxHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty AutoSuggestBoxHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool AutoSuggestBoxHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& autoSuggestBox)
	{
		return winrt::unbox_value<bool>(autoSuggestBox.GetValue(AcrylicWorkaroundProperty()));
	}

	void AutoSuggestBoxHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox const& autoSuggestBox,
		bool value
	)
	{
		autoSuggestBox.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	void AutoSuggestBoxHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;
		
		auto autoSuggestBox = object.as<winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox>();
		auto layoutUpdatedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox::LayoutUpdated_revoker>();
		*layoutUpdatedRevoker = autoSuggestBox.LayoutUpdated(winrt::auto_revoke, [autoSuggestBoxRef = winrt::make_weak(autoSuggestBox), layoutUpdatedRevoker](auto&&...)
		{
			auto popup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(
				autoSuggestBoxRef.get().as<winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox>(), 
				L"SuggestionsPopup"
			);
			if (!popup) 
				return;


			auto borderRef = popup.FindName(L"SuggestionsContainer");
			if (!borderRef)
				return;

			layoutUpdatedRevoker->revoke();
			auto border = borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>();
			border.Padding({});
			border.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });

			
			auto borderLoadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::Border::Loaded_revoker>();
			*borderLoadedRevoker = border.Loaded(winrt::auto_revoke, [borderLoadedRevoker](auto const& borderRef, auto&&)
			{
				borderLoadedRevoker->revoke();
				
				auto border = borderRef.as<winrt::Microsoft::UI::Xaml::Controls::Border>();
				auto originalChild = border.Child();
				winrt::Microsoft::UI::Xaml::Controls::Grid scrollGrid;
				border.Child(scrollGrid);

				winrt::WinUI3Package::AcrylicVisual visual;

				winrt::Microsoft::UI::Xaml::Data::Binding cornerRadiusBinding;
				cornerRadiusBinding.Source(border);
				cornerRadiusBinding.Path(winrt::Microsoft::UI::Xaml::PropertyPath{ L"CornerRadius" });
				visual.SetBinding(
					winrt::Microsoft::UI::Xaml::Controls::Control::CornerRadiusProperty(),
					cornerRadiusBinding
				);
				scrollGrid.Children().ReplaceAll({ visual, originalChild });
			});
		});

	}
}
