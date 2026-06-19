#include "pch.h"
#include "CrossFadeEffectInterop.h"
#include "EffectPropertyHelper.h"

HRESULT CrossFadeInterop::getPropertyImpl(UINT index, ABI::Windows::Foundation::IPropertyValue** value)
{
	if (index == D2D1_CROSSFADE_PROP::D2D1_CROSSFADE_PROP_WEIGHT)
		return EffectPropertyHelper::MakeProperty(m_crossFade, value);

	return E_INVALIDARG;
}

HRESULT CrossFadeInterop::getSourceImpl(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source)
{
	if (index >= sourceCount)
		return E_FAIL;

	if (index == 0)
		m_source1.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
	else
		m_source2.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
	return S_OK;
}

CrossFadeInterop::CrossFadeInterop(float initialCrossFade, wchar_t const* source1, wchar_t const* source2) :
	m_crossFade{ initialCrossFade },
	m_source1{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source1} },
	m_source2{ winrt::Windows::UI::Composition::CompositionEffectSourceParameter{source2} }
{
}
