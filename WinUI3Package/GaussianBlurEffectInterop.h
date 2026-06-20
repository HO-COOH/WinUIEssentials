#pragma once
#include "EffectInterop.hpp"
#include "EffectPropertyMapping.h"
#include <d2d1effects.h>

class GaussianBlurEffectInterop : public EffectInterop<GaussianBlurEffectInterop> 
{
	float BlurAmount;
	UINT32 Optimization{ static_cast<UINT32>(D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED) };
	UINT32 BorderMode{ static_cast<UINT32>(D2D1_BORDER_MODE_HARD) };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource Source{ nullptr };

	static inline constexpr EffectPropertyMapping<GaussianBlurEffectInterop> propertyMappings[]
	{
		{
			.name = L"BlurAmount",
			.index = D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION,
			.mapping = ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
			.source = &GaussianBlurEffectInterop::BlurAmount
		},
		{
			.name = L"Optimization",
			.index = D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION,
			.mapping = ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
			.source = &GaussianBlurEffectInterop::Optimization
		},
		{
			.name = L"BorderMode",
			.index = D2D1_GAUSSIANBLUR_PROP_BORDER_MODE,
			.mapping = ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
			.source = &GaussianBlurEffectInterop::BorderMode
		}
	};

	static inline constexpr std::array sources
	{
		&GaussianBlurEffectInterop::Source
	};

	static inline const GUID EffectId = CLSID_D2D1GaussianBlur;
	
	friend class EffectInterop<GaussianBlurEffectInterop>;
public:
	GaussianBlurEffectInterop(
		float blurAmount,
		wchar_t const* source
	);
};