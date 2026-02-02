#pragma once
#include "EffectInterop.hpp"
#include "EffectPropertyMapping.h"
#include <d2d1effects_2.h>

class CrossFadeInterop : public EffectInterop<CrossFadeInterop>
{
	friend class EffectInterop<CrossFadeInterop>;

	static inline const GUID EffectId = CLSID_D2D1CrossFade;
	static inline constexpr UINT sourceCount = 2;
	static inline constexpr EffectPropertyMapping propertyMappings[]
	{
		{
			L"CrossFade",
			D2D1_CROSSFADE_PROP::D2D1_CROSSFADE_PROP_WEIGHT,
			ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT
		}
	};

	HRESULT getPropertyImpl(UINT index, ABI::Windows::Foundation::IPropertyValue** value)
	{
		if (index == D2D1_CROSSFADE_PROP::D2D1_CROSSFADE_PROP_WEIGHT)
			return makeProperty(CrossFade, value);

		return E_INVALIDARG;
	}

	HRESULT getSourceImpl(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source)
	{
		if (index >= sourceCount || !Source1 || !Source2)
			return E_FAIL;

		if (index == 0)
			Source1.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
		else
			Source2.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
		return S_OK;
	}

public:
	float CrossFade{ 0.5f };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource Source1{ nullptr };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource Source2{ nullptr };
};