#pragma once
#include <winrt/Microsoft.UI.Composition.h>

class RevealBrush : public winrt::Microsoft::UI::Composition::CompositionRadialGradientBrush
{
public:
	RevealBrush(winrt::Microsoft::UI::Composition::Compositor const& compositor);

	constexpr static winrt::Windows::Foundation::Numerics::float2 NormalRevealRadius{ 75.f, 75.f };
};

