#include "pch.h"
#include "CrossFadeEffectInterop.h"
#include "EffectPropertyHelper.h"

CrossFadeInterop::CrossFadeInterop(float initialCrossFade, wchar_t const* source1, wchar_t const* source2) :
	m_crossFade{ initialCrossFade },
	m_source1{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source1} },
	m_source2{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source2} }
{
}
