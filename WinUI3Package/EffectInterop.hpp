#pragma once
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.Foundation.h>
#include <windows.graphics.effects.interop.h>

// CRTP base class for D2D1 effect interop
// Derived class must provide:
//   - static inline const GUID EffectId
//   - static inline constexpr UINT sourceCount
//   - static inline const EffectPropertyMapping propertyMappings[]
//   - HRESULT getPropertyImpl(UINT index, ABI::Windows::Foundation::IPropertyValue** value)
//   - HRESULT getSourceImpl(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source)
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
		return static_cast<Derived*>(this)->getPropertyImpl(index, value);
	}

	IFACEMETHODIMP GetSource(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source) override
	{
		return static_cast<Derived*>(this)->getSourceImpl(index, source);
	}

	IFACEMETHODIMP GetSourceCount(UINT* count) override
	{
		*count = Derived::sourceCount;
		return S_OK;
	}
};