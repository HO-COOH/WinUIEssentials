#pragma once
#include "EffectInterop.hpp"
#include "EffectPropertyMapping.h"
#include <d2d1effects_2.h>

class CrossFadeInterop : public EffectInterop<CrossFadeInterop>
{
	float m_crossFade{ 0.5f };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source1{ nullptr };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source2{ nullptr };

	static inline const GUID EffectId = CLSID_D2D1CrossFade;

	static inline constexpr EffectPropertyMapping<CrossFadeInterop> propertyMappings[]
	{
		{
			.name = L"CrossFade",
			.index = D2D1_CROSSFADE_PROP::D2D1_CROSSFADE_PROP_WEIGHT,
			.mapping = ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
			.source = &CrossFadeInterop::m_crossFade
		}
	};

	static inline constexpr std::array sources
	{
		&CrossFadeInterop::m_source1,
		&CrossFadeInterop::m_source2
	};

	friend class EffectInterop<CrossFadeInterop>;
public:
	CrossFadeInterop(float initialCrossFade, wchar_t const* source1, wchar_t const* source2);
};