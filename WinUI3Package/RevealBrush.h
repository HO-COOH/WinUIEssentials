#pragma once
#include <winrt/Microsoft.UI.Composition.h>

class RevealBrush : public winrt::Microsoft::UI::Composition::CompositionRadialGradientBrush
{
public:
	RevealBrush(winrt::Microsoft::UI::Composition::Compositor const& compositor);
};

