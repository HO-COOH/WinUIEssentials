#include "pch.h"
#include "MediaPlayerElementHelper.h"
#if __has_include("MediaPlayerElementHelper.g.cpp")
#include "MediaPlayerElementHelper.g.cpp"
#endif
#include "MediaTransportControlsHelper.h"

namespace winrt::WinUI3Package::implementation
{
	winrt::Microsoft::UI::Xaml::DependencyProperty MediaPlayerElementHelper::s_acrylicWorkaroundProperty =
		winrt::Microsoft::UI::Xaml::DependencyProperty::RegisterAttached(
			L"AcrylicWorkaround",
			winrt::xaml_typename<bool>(),
			winrt::xaml_typename<winrt::WinUI3Package::MediaPlayerElementHelper>(),
			winrt::Microsoft::UI::Xaml::PropertyMetadata{
				nullptr,
				&MediaPlayerElementHelper::acrylicWorkaroundChanged
			}
		);

	bool MediaPlayerElementHelper::GetAcrylicWorkaround(winrt::Microsoft::UI::Xaml::Controls::MediaPlayerElement const& MediaPlayerElement)
	{
		return winrt::unbox_value<bool>(MediaPlayerElement.GetValue(s_acrylicWorkaroundProperty));
	}

	void MediaPlayerElementHelper::SetAcrylicWorkaround(
		winrt::Microsoft::UI::Xaml::Controls::MediaPlayerElement const& MediaPlayerElement,
		bool value
	)
	{
		MediaPlayerElement.SetValue(s_acrylicWorkaroundProperty, winrt::box_value(value));
	}

	winrt::Microsoft::UI::Xaml::DependencyProperty MediaPlayerElementHelper::AcrylicWorkaroundProperty()
	{
		return s_acrylicWorkaroundProperty;
	}

	void MediaPlayerElementHelper::acrylicWorkaroundChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& d,
		winrt::Microsoft::UI::Xaml::DependencyPropertyChangedEventArgs const& e
	)
	{
		auto const acrylicWorkaround = winrt::unbox_value<bool>(e.NewValue());
		if (!acrylicWorkaround)
			return;

		auto mediaPlayerElement = d.as<winrt::Microsoft::UI::Xaml::Controls::MediaPlayerElement>();
		if (auto transportControls = mediaPlayerElement.TransportControls())
			MediaTransportControlsHelper::ApplyAcrylicToMediaTransportControl(transportControls);
	}
}
