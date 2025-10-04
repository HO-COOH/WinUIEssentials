#include "pch.h"
#include "CommandBarHelper.h"
#if __has_include("CommandBarHelper.g.cpp")
#include "CommandBarHelper.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include "VisualTreeHelper.hpp"
#include "AcrylicVisualWithBoundedCornerRadius.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty CommandBarHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::Microsoft::UI::Xaml::Controls::CommandBar>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{ winrt::box_value(false), winrt::Microsoft::UI::Xaml::PropertyChangedCallback(&CommandBarHelper::acrylicWorkaroundChanged) }
		);

	winrt::Microsoft::UI::Xaml::DependencyProperty CommandBarHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	bool CommandBarHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::CommandBar const& commandBar)
	{
		return winrt::unbox_value<bool>(commandBar.GetValue(s_acrylicWorkaroundProperty));
	}

	void CommandBarHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::CommandBar const& commandBar,
		bool value
	)
	{
		commandBar.SetValue(s_acrylicWorkaroundProperty, winrt::box_value(value));
	}

	void CommandBarHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& object,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& arg
	)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(arg.NewValue());
		if (!acrylicWorkaround)
			return;

		auto commandBar = object.as<winrt::Microsoft::UI::Xaml::Controls::CommandBar>();

		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::CommandBar::Loaded_revoker>();
		*loadedRevoker = commandBar.Loaded(winrt::auto_revoke, [loadedRevoker](auto&& self, auto&&)
		{
			loadedRevoker->revoke();

			auto commandBar = self.as<winrt::Microsoft::UI::Xaml::Controls::CommandBar>();
			auto overflowPopup = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>(commandBar, L"OverflowPopup");
			auto openedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup::Opened_revoker>();
			*openedRevoker = overflowPopup.Opened(winrt::auto_revoke, [openedRevoker](auto&& self, auto&&)
			{
				openedRevoker->revoke();

				auto popup = self.as<winrt::Microsoft::UI::Xaml::Controls::Primitives::Popup>();
				auto secondaryItemsControl = popup.FindName(L"SecondaryItemsControl").as<winrt::Microsoft::UI::Xaml::Controls::CommandBarOverflowPresenter>();
				auto OverflowContentRoot = popup.FindName(L"SecondaryItemsControlShadowWrapper").as<winrt::Microsoft::UI::Xaml::Controls::Grid>();
				OverflowContentRoot.Children().InsertAt(0, AcrylicVisualWithBoundedCornerRadius{secondaryItemsControl});
				secondaryItemsControl.Background(winrt::Microsoft::UI::Xaml::Media::SolidColorBrush{ winrt::Windows::UI::Colors::Transparent() });
			});
		});
	}
}
