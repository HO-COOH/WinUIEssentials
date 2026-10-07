#include "pch.h"
#include "BlendEffectInterop.h"

BlendEffectInterop::BlendEffectInterop(D2D1_BLEND_MODE mode, wchar_t const* source1, wchar_t const* source2) :
	m_mode{ static_cast<UINT32>(mode) },
	m_source1{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source1} },
	m_source2{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source2} }
{
}

BlendEffectInterop::BlendEffectInterop(D2D1_BLEND_MODE mode, winrt::Windows::Graphics::Effects::IGraphicsEffectSource const& source1, wchar_t const* source2) :
	m_mode{ static_cast<UINT32>(mode) }, 
	m_source1{ source1 },
	m_source2{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source2} }
{
}
