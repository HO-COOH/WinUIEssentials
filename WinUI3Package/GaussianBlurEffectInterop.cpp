#include "pch.h"
#include "GaussianBlurEffectInterop.h"

GaussianBlurEffectInterop::GaussianBlurEffectInterop(float blurAmount, wchar_t const* source) :
	BlurAmount{blurAmount},
	Source{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Backdrop" } }
{
}
