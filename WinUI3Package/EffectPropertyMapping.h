#pragma once
#include <windows.graphics.effects.interop.h>

struct EffectPropertyMapping
{
	const wchar_t* name;
	UINT index;
	ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING mapping;
};