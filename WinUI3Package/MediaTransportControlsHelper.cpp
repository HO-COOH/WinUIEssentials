#include "pch.h"
#include "MediaTransportControlsHelper.h"
#if __has_include("MediaTransportControlsHelper.g.cpp")
#include "MediaTransportControlsHelper.g.cpp"
#endif
#include "VisualTreeHelper.hpp"
#include "AcrylicVisualWithBoundedCornerRadius.h"


namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty MediaTransportControlsHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::WinUI3Package::MediaTransportControlsHelper>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&MediaTransportControlsHelper::acrylicWorkaroundChanged
			}
		);

	bool MediaTransportControlsHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& MediaTransportControls)
	{
		return winrt::unbox_value<bool>(MediaTransportControls.GetValue(s_acrylicWorkaroundProperty));
	}

	void MediaTransportControlsHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& MediaTransportControls,
		bool value
	)
	{
		MediaTransportControls.SetValue(s_acrylicWorkaroundProperty, winrt::box_value(value));
	}

	static void applyAcrylicWorkaroundToButtonToolTip(wchar_t const* buttonName, winrt::Microsoft::UI::Xaml::Controls::Grid const& ControlPanelGrid)
	{
		auto PlayPauseButton = ControlPanelGrid.FindName(buttonName);
		if (!PlayPauseButton)
			return;

		auto button = PlayPauseButton.try_as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		if (!button)
			return;

		auto tooltip = winrt::Microsoft::UI::Xaml::Controls::ToolTipService::GetToolTip(button);
		if (!tooltip)
			return;

		if (auto tip = tooltip.try_as<winrt::Microsoft::UI::Xaml::Controls::ToolTip>())
			winrt::WinUI3Package::ToolTipHelper::SetAcrylicWorkaround(tip, true);
	}

	void MediaTransportControlsHelper::ApplyAcrylicToMediaTransportControl(winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& mediaTransportControls)
	{
		if (mediaTransportControls.IsLoaded())
		{
			applyAcrylicToMediaTransportControlAfterLoaded(mediaTransportControls);
			return;
		}

		auto loadedRevoker = std::make_shared<winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls::Loaded_revoker>();
		*loadedRevoker = mediaTransportControls.Loaded(winrt::auto_revoke, [loadedRevoker](auto const& self, auto const&)
		{
			loadedRevoker->revoke();
			applyAcrylicToMediaTransportControlAfterLoaded(self.as<winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls>());
		});
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty MediaTransportControlsHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	void MediaTransportControlsHelper::applyAcrylicToMediaTransportControlAfterLoaded(winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls const& mediaTransportControls)
	{
		// Find the ControlPanelGrid in the visual tree
		auto ControlPanelGrid = VisualTreeHelper::FindVisualChildByName<winrt::Microsoft::UI::Xaml::Controls::Grid>(
			mediaTransportControls,
			L"ControlPanelGrid"
		);
		AcrylicVisualWithBoundedCornerRadius<winrt::WinUI3Package::InAppAcrylicVisual> acrylicVisual{ ControlPanelGrid };
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetRowSpan(acrylicVisual, ControlPanelGrid.RowDefinitions().Size());
		winrt::Microsoft::UI::Xaml::Controls::Grid::SetColumnSpan(acrylicVisual, ControlPanelGrid.ColumnDefinitions().Size());
		ControlPanelGrid.Children().InsertAt(0, acrylicVisual);

		//CompactMode VisualState sets ControlPanelGrid.Padding, we need to extend the visual
		auto const coverPadding = [weakAcrylicVisual = winrt::make_weak<winrt::Microsoft::UI::Xaml::FrameworkElement>(acrylicVisual)](
			winrt::Microsoft::UI::Xaml::DependencyObject const& grid,
			winrt::Microsoft::UI::Xaml::DependencyProperty const& paddingProperty)
		{
			if (auto acrylicVisual = weakAcrylicVisual.get())
			{
				auto const padding = winrt::unbox_value<winrt::Microsoft::UI::Xaml::Thickness>(grid.GetValue(paddingProperty));
				acrylicVisual.Margin({ -padding.Left, -padding.Top, -padding.Right, -padding.Bottom });
			}
		};
		coverPadding(ControlPanelGrid, winrt::Microsoft::UI::Xaml::Controls::Grid::PaddingProperty());
		ControlPanelGrid.RegisterPropertyChangedCallback(winrt::Microsoft::UI::Xaml::Controls::Grid::PaddingProperty(), coverPadding);

		//Volumn control
		if (auto VolumnFlyout = ControlPanelGrid.FindName(L"VolumeFlyout"))
		{
			if (auto flyout = VolumnFlyout.try_as<winrt::Microsoft::UI::Xaml::Controls::Flyout>())
				winrt::WinUI3Package::FlyoutHelper::SetAcrylicWorkaround(flyout, true);
		}

		//Audio track selection flyout is dynamically created, we need to listen to the FlyoutProperty
		if (auto AudioTracksSelectionButton = ControlPanelGrid.FindName(L"AudioTracksSelectionButton"))
		{
			if (auto button = AudioTracksSelectionButton.try_as<winrt::Microsoft::UI::Xaml::Controls::Button>())
			{
				button.RegisterPropertyChangedCallback(
					winrt::Microsoft::UI::Xaml::Controls::Button::FlyoutProperty(),
					[](winrt::Microsoft::UI::Xaml::DependencyObject const& d, winrt::Microsoft::UI::Xaml::DependencyProperty const& dp)
					{
						if (auto flyout = d.GetValue(dp).try_as<winrt::Microsoft::UI::Xaml::Controls::Flyout>())
							winrt::WinUI3Package::FlyoutHelper::SetAcrylicWorkaround(flyout, true);
					}
				);
			}
		}

		//buttons, see Generic.xaml Line 28300+
		applyAcrylicWorkaroundToButtonToolTip(L"VolumeMuteButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"CCselectionButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"AudioTracksSelectionButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"StopButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"SkipBackwardButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"PreviousTrackButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"RewindButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"PlayPauseButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"FastForwardButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"NextTrackButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"SkipForwardButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"PlaybackRateButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"RepeatButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"ZoomButton", ControlPanelGrid);
		applyAcrylicWorkaroundToButtonToolTip(L"CastButton", ControlPanelGrid);
	}

	void MediaTransportControlsHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(e.NewValue());
		if (!acrylicWorkaround)
			return;

		auto mediaTransportControls = d.try_as<winrt::Microsoft::UI::Xaml::Controls::MediaTransportControls>();
		ApplyAcrylicToMediaTransportControl(mediaTransportControls);
	}
}
