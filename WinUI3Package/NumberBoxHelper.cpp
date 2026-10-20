#include "pch.h"
#include "NumberBoxHelper.h"
#if __has_include("NumberBoxHelper.g.cpp")
#include "NumberBoxHelper.g.cpp"
#endif
#include "AcrylicVisualWithBoundedCornerRadius.h"
#include "BindingHelper.h"
#include "GridHelper.hpp"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty NumberBoxHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::WinUI3Package::NumberBoxHelper>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&NumberBoxHelper::acrylicWorkaroundChanged
			}
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty NumberBoxHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool NumberBoxHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& numberBox)
	{
		return winrt::unbox_value<bool>(numberBox.GetValue(s_acrylicWorkaroundProperty));
	}

	void NumberBoxHelper::SetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NumberBox const& numberBox, bool value)
	{
		numberBox.SetValue(s_acrylicWorkaroundProperty, winrt::box_value(value));
	}

	void NumberBoxHelper::acrylicWorkaroundChanged(winrt::Microsoft::UI::Xaml::DependencyObject const& object, winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::NumberBox::Loaded_revoker>();
		*loadedRevoker = object.as<winrt::Microsoft::UI::Xaml::Controls::NumberBox>().Loaded(winrt::auto_revoke, [loadedRevoker](auto const& self, auto&&)
		{
			loadedRevoker->revoke();

			auto numberBox = self.as<winrt::Microsoft::UI::Xaml::Controls::NumberBox>();
			auto templateRoot = winrt::Microsoft::UI::Xaml::Media::VisualTreeHelper::GetChild(numberBox, 0).try_as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
			if (!templateRoot)
				return;

			auto PopupContentRoot = templateRoot.FindName(L"PopupContentRoot").try_as<winrt::Microsoft::UI::Xaml::Controls::Grid>();
			if (!PopupContentRoot)
				return;

			AcrylicVisualWithBoundedCornerRadius acrylicVisual{ PopupContentRoot };
			GridHelper::SpanGrid<true, false>(acrylicVisual, PopupContentRoot);

			//PopupContentRoot has Padding="6", extend the visual
			auto const padding = PopupContentRoot.Padding();
			acrylicVisual.Margin({ -padding.Left, -padding.Top, -padding.Right, -padding.Bottom });

			//The acrylic in UpDownPopup does not follow theme changes of the NumberBox, sync it manually
			acrylicVisual.RequestedTheme(numberBox.ActualTheme());
			BindingHelper::BindTheme(acrylicVisual, numberBox);

			PopupContentRoot.Children().InsertAt(0, acrylicVisual);
		});
	}

}
