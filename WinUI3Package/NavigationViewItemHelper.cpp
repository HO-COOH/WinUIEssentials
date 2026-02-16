#include "pch.h"
#include "NavigationViewItemHelper.h"
#if __has_include("NavigationViewItemHelper.g.cpp")
#include "NavigationViewItemHelper.g.cpp"
#endif

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty NavigationViewItemHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<class_type>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata(
				winrt::box_value(false),
				winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&NavigationViewItemHelper::acrylicWorkaroundChanged)
			)
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty NavigationViewItemHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool NavigationViewItemHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem const& navigationViewItem)
	{
		return winrt::unbox_value<bool>(navigationViewItem.GetValue(AcrylicWorkaroundProperty()));
	}

	void NavigationViewItemHelper::SetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem const& navigationViewItem, bool value)
	{
		navigationViewItem.SetValue(AcrylicWorkaroundProperty(), winrt::box_value(value));
	}

	void NavigationViewItemHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg)
	{
		auto const value = winrt::unbox_value<bool>(arg.NewValue());

		if (!value) return;

		auto navigationViewItem = object.as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();

		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::FrameworkElement::Loaded_revoker>();
		*loadedRevoker = object.as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>().Loaded(winrt::auto_revoke, [loadedRevoker](winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const&)
		{
			auto navigationViewItem = sender.as<winrt::Microsoft::UI::Xaml::Controls::NavigationViewItem>();

			auto toolTipContent = winrt::Microsoft::UI::Xaml::Controls::ToolTipService::GetToolTip(navigationViewItem).try_as<winrt::hstring>();

			winrt::Microsoft::UI::Xaml::Controls::ToolTip toolTip = {};
			toolTip.Content(winrt::box_value(*toolTipContent));
			toolTip.Placement(winrt::Microsoft::UI::Xaml::Controls::Primitives::PlacementMode::Mouse);
			winrt::WinUI3Package::ToolTipHelper::SetAcrylicWorkaround(toolTip, true);

			winrt::Microsoft::UI::Xaml::Controls::ToolTipService::SetToolTip(navigationViewItem, toolTip);

			loadedRevoker->revoke();
		});


	}

}
