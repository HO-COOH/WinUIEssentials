#pragma once
#include <windows.foundation.h>

namespace ABI::Windows::Graphics::Effects
{
	struct IGraphicsEffectSource;
}

namespace EffectPropertyHelper
{
	// Overloaded helpers to create property values
	HRESULT MakeProperty(float value, ABI::Windows::Foundation::IPropertyValue** result);
	HRESULT MakeProperty(double value, ABI::Windows::Foundation::IPropertyValue** result);
	HRESULT MakeProperty(UINT32 value, ABI::Windows::Foundation::IPropertyValue** result);
	HRESULT MakeProperty(INT32 value, ABI::Windows::Foundation::IPropertyValue** result);
	HRESULT MakeProperty(bool value, ABI::Windows::Foundation::IPropertyValue** result);
	HRESULT ReturnSource(
		winrt::Windows::Graphics::Effects::IGraphicsEffectSource& source,
		ABI::Windows::Graphics::Effects::IGraphicsEffectSource** outValue);
}
