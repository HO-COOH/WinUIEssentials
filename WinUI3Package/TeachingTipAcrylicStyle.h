#pragma once
#include <winrt/base.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "TeachingTipOutline.h"

class TargetedTeachingTipAcrylicStyle
{
	void resizeAndTranslateTailAcrylic(TeachingTipOutline const& outline, winrt::Windows::Foundation::Rect const& bodyAcrylic);
	void onLayoutChanged();
	void compareAndSetOutlinePath(TeachingTipOutline&& outline);
	static winrt::WinUI3Package::AcrylicVisual makeRotatedTailAcrylicVisual();

	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Shapes::Path> m_outlinePath;
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::Canvas> m_tailCanvas;
	winrt::weak_ref<winrt::WinUI3Package::AcrylicVisual> m_tailAcrylicVisual;
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::Grid> m_tailOcclusionGrid;
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Controls::Grid> m_contentRootGrid;
	winrt::weak_ref<winrt::Microsoft::UI::Xaml::Shapes::Polygon> m_tailPolygon;
	TeachingTipOutline m_lastOutline;
public:
	/*
		Applies the style, and follows the layout of the TailOcclusionGrid from then on
		The TailOcclusionGrid's LayoutUpdated handler keeps a copy of this object, so the constructed one does not need to be kept
		neither does it needs to be constructed as a shared_ptr
	*/
	TargetedTeachingTipAcrylicStyle(
		winrt::Microsoft::UI::Xaml::Controls::TeachingTip const& teachingTip,
		winrt::Microsoft::UI::Xaml::Controls::Grid const& tailOcclusionGrid,
		winrt::Microsoft::UI::Xaml::Controls::Grid const& contentRootGrid,
		winrt::Microsoft::UI::Xaml::Shapes::Polygon const& tailPolygon
	);
};
