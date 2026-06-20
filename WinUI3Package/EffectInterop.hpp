#pragma once
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.Foundation.h>
#include <windows.graphics.effects.interop.h>
#include <array>
#include "EffectPropertyHelper.h"

// CRTP base class for D2D1 effect interop
// Derived class must provide:
//   - static inline const GUID EffectId
//   - static inline const EffectPropertyMapping<Derived> propertyMappings[]
//       (each entry's `.source` is a pointer-to-member naming the field that backs the property;
//        the base reads it via std::visit, no per-derived getPropertyImpl needed)
//   - static inline constexpr std::array sources{ &Derived::m_src1, ... }
//       (pointer-to-members of type winrt::Windows::Graphics::Effects::IGraphicsEffectSource;
//        size of array is also the source count — no separate sourceCount needed)
template<typename Derived>
class EffectInterop : public winrt::implements<
	Derived,
	winrt::Windows::Graphics::Effects::IGraphicsEffect,
	winrt::Windows::Graphics::Effects::IGraphicsEffectSource,
	ABI::Windows::Graphics::Effects::IGraphicsEffectD2D1Interop
>
{
	winrt::hstring m_name;
public:
	// IGraphicsEffect
	winrt::hstring Name() { return m_name; }
	void Name(winrt::hstring const& value) { m_name = value; }

	// IGraphicsEffectD2D1Interop
	IFACEMETHODIMP GetEffectId(GUID* id) override
	{
		*id = Derived::EffectId;
		return S_OK;
	}

	IFACEMETHODIMP GetNamedPropertyMapping(
		LPCWSTR name,
		UINT* index,
		ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) override
	{
		for (auto const& prop : Derived::propertyMappings)
		{
			if (wcscmp(name, prop.name) == 0)
			{
				*index = prop.index;
				*mapping = prop.mapping;
				return S_OK;
			}
		}
		return E_INVALIDARG;
	}

	IFACEMETHODIMP GetPropertyCount(UINT* count) override
	{
		*count = static_cast<UINT>(std::size(Derived::propertyMappings));
		return S_OK;
	}

	IFACEMETHODIMP GetProperty(UINT index, ABI::Windows::Foundation::IPropertyValue** value) override
	{
		auto* self = static_cast<Derived*>(this);
		for (auto const& prop : Derived::propertyMappings)
		{
			if (prop.index != index)
				continue;

			return std::visit([&](auto memberPtr)
			{
				return EffectPropertyHelper::MakeProperty(self->*memberPtr, value);
			}, prop.source);
		}
		return E_INVALIDARG;
	}

	IFACEMETHODIMP GetSource(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source) override
	{
		if (index >= std::size(Derived::sources))
			return E_FAIL;

		auto& field = static_cast<Derived*>(this)->*(Derived::sources[index]);
		if (!field)
			return E_FAIL;

		field.template as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
		return S_OK;
	}

	IFACEMETHODIMP GetSourceCount(UINT* count) override
	{
		*count = static_cast<UINT>(std::size(Derived::sources));
		return S_OK;
	}
};