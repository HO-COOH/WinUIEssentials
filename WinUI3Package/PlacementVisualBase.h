#pragma once

#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

/*
	Hosts a placement visual as the child visual of a control, keeping it sized to the control
	and clipped to the control's CornerRadius.
*/
class PlacementVisualBase
{
protected:
	winrt::Microsoft::UI::Composition::Visual m_placementVisual{ nullptr };
	//Call after the placement visual is attached to the host
	void BindPlacementVisualSizeToHost(winrt::Microsoft::UI::Xaml::UIElement const& host);
private:
	PlacementVisualBase(winrt::Microsoft::UI::Xaml::Controls::Control const& host);
	winrt::Microsoft::UI::Composition::RectangleClip m_clip{ nullptr };
	void cornerRadiusChanged(
		winrt::Microsoft::UI::Xaml::DependencyObject const& host,
		winrt::Microsoft::UI::Xaml::DependencyProperty const& cornerRadiusProperty
	);
};
