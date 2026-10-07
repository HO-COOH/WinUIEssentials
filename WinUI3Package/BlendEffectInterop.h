#pragma once
#include "EffectInterop.hpp"
#include "EffectPropertyMapping.h"
#include <d2d1effects.h>

class BlendEffectInterop : public EffectInterop<BlendEffectInterop>
{
	UINT32 m_mode;
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source1{ nullptr };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source2{ nullptr };

	static inline const GUID EffectId = CLSID_D2D1Blend;

	static inline constexpr EffectPropertyMapping<BlendEffectInterop> propertyMappings[]
	{
		{
			.name = L"Mode",
			.index = D2D1_BLEND_PROP_MODE,
			.mapping = ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
			.source = &BlendEffectInterop::m_mode
		}
	};

	static inline constexpr std::array sources
	{
		&BlendEffectInterop::m_source1,
		&BlendEffectInterop::m_source2
	};
	friend class EffectInterop<BlendEffectInterop>;
public:
	BlendEffectInterop(D2D1_BLEND_MODE mode, wchar_t const* source1, wchar_t const* source2);
	BlendEffectInterop(D2D1_BLEND_MODE mode, winrt::Windows::Graphics::Effects::IGraphicsEffectSource const& source1, wchar_t const* source2);
};