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
			.name = L"CrossFade",
			.index = D2D1_CROSSFADE_PROP::D2D1_CROSSFADE_PROP_WEIGHT,
			.mapping = ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT
		}
	};

	HRESULT getPropertyImpl(UINT index, ABI::Windows::Foundation::IPropertyValue** value);
	HRESULT getSourceImpl(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source);

	float m_crossFade{ 0.5f };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source1{ nullptr };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source2{ nullptr };
public:
	CrossFadeInterop(
		float initialCrossFade,
		wchar_t const* source1,
		wchar_t const* source2
	);
};