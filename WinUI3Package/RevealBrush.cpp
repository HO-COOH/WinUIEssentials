#include "pch.h"
#include <winrt/Windows.UI.h>
#include "RevealBrush.h"

RevealBrush::RevealBrush(winrt::Microsoft::UI::Composition::Compositor const& compositor)
	: CompositionRadialGradientBrush{ compositor.CreateRadialGradientBrush() }
{
	ColorStops().ReplaceAll({
		compositor.CreateColorGradientStop(0.0f, winrt::Windows::UI::ColorHelper::FromArgb(0, 100, 150, 255)),
		compositor.CreateColorGradientStop(0.3f, winrt::Windows::UI::ColorHelper::FromArgb(0, 80, 130, 255)),
		compositor.CreateColorGradientStop(0.6f, winrt::Windows::UI::ColorHelper::FromArgb(0, 60, 110, 255)),
		compositor.CreateColorGradientStop(1.0f, winrt::Windows::UI::ColorHelper::FromArgb(0, 40, 90, 255))
		//compositor.CreateColorGradientStop(0.0f, winrt::Windows::UI::Colors::White()),
		//compositor.CreateColorGradientStop(1.f, winrt::Windows::UI::Colors::Transparent())
	});

	EllipseRadius({ 100.f, 100.f });
	MappingMode(winrt::Microsoft::UI::Composition::CompositionMappingMode::Absolute);
}
