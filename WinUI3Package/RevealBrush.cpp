#include "pch.h"
#include <winrt/Windows.UI.h>
#include "RevealBrush.h"

RevealBrush::RevealBrush(winrt::Microsoft::UI::Composition::Compositor const& compositor)
	: CompositionRadialGradientBrush{ compositor.CreateRadialGradientBrush() }
{
	ColorStops().ReplaceAll({
		//compositor.CreateColorGradientStop(0.0f, winrt::Windows::UI::ColorHelper::FromArgb(255, 100, 150, 255)),
		//compositor.CreateColorGradientStop(0.3f, winrt::Windows::UI::ColorHelper::FromArgb(180, 80, 130, 255)),
		//compositor.CreateColorGradientStop(0.6f, winrt::Windows::UI::ColorHelper::FromArgb(60, 60, 110, 255)),
		//compositor.CreateColorGradientStop(1.0f, winrt::Windows::UI::ColorHelper::FromArgb(0, 40, 90, 255))
		compositor.CreateColorGradientStop(0.0f, winrt::Windows::UI::ColorHelper::FromArgb(255, 0xb9, 0xb9, 0xb9)),
		//compositor.CreateColorGradientStop(0.1f, winrt::Windows::UI::ColorHelper::FromArgb(200, 0xc9, 0xc9, 0xc9)),
		//compositor.CreateColorGradientStop(0.1f, winrt::Windows::UI::ColorHelper::FromArgb(, 0xc9, 0xc9, 0xc9)),
		compositor.CreateColorGradientStop(1.f, winrt::Windows::UI::ColorHelper::FromArgb(0, 0xb9, 0xb9, 0xb9))
	});

	EllipseRadius(NormalRevealRadius);
	MappingMode(winrt::Microsoft::UI::Composition::CompositionMappingMode::Absolute);
}
