#pragma once
#include "EffectInterop.hpp"
#include "EffectPropertyMapping.h"
#include <d2d1effects.h>

class BlurEffectInterop : public EffectInterop<BlurEffectInterop>
{
	friend class EffectInterop<BlurEffectInterop>;

	static inline const GUID EffectId = CLSID_D2D1GaussianBlur;
	static inline constexpr UINT sourceCount = 1;
	static inline constexpr EffectPropertyMapping propertyMappings[]
	{
		{
			L"Radius",
			D2D1_GAUSSIANBLUR_PROP::D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION,
			ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT
		},
		{
			L"Optimization",
			D2D1_GAUSSIANBLUR_PROP::D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION,
			ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT
		},
		{
			L"BorderMode",
			D2D1_GAUSSIANBLUR_PROP::D2D1_GAUSSIANBLUR_PROP_BORDER_MODE,
			ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT
		},
	};
	
	HRESULT getPropertyImpl(UINT index, ABI::Windows::Foundation::IPropertyValue** value)
	{
		switch (index)
		{
			case D2D1_GAUSSIANBLUR_PROP::D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION:
				return makeProperty(Radius, value);
			case D2D1_GAUSSIANBLUR_PROP::D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION:
				return makeProperty(static_cast<UINT32>(Optimization), value);
			case D2D1_GAUSSIANBLUR_PROP::D2D1_GAUSSIANBLUR_PROP_BORDER_MODE:
				return makeProperty(static_cast<UINT32>(BorderMode), value);
			default:
				return E_INVALIDARG;
		}
	}

	HRESULT getSourceImpl(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source)
	{
		if (index >= sourceCount || !Source)
			return E_FAIL;
		Source.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
		return S_OK;
	}

public:
	float Radius{ 1.0f };
	D2D1_GAUSSIANBLUR_OPTIMIZATION Optimization{ D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED };
	D2D1_BORDER_MODE BorderMode{ D2D1_BORDER_MODE_SOFT };
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource Source{ nullptr };
};