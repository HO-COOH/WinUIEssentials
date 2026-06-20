#pragma once
#include <windows.graphics.effects.interop.h>
#include <variant>

template<typename Derived>
struct EffectPropertyMapping
{
	const wchar_t* name;
	UINT index;
	ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING mapping;
	std::variant<
		float Derived::*,
		double Derived::*,
		UINT32 Derived::*,
		INT32 Derived::*,
		bool Derived::*
	> source;
};