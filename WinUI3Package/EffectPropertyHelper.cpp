#include "pch.h"
#include "EffectPropertyHelper.h"
#include <windows.graphics.effects.h>
#include <winrt/Windows.Graphics.Effects.h>

namespace EffectPropertyHelper
{
	HRESULT MakeProperty(float value, ABI::Windows::Foundation::IPropertyValue** result)
	{
		auto pv = winrt::Windows::Foundation::PropertyValue::CreateSingle(value);
		pv.as<ABI::Windows::Foundation::IPropertyValue>().copy_to(result);
		return S_OK;
	}

	HRESULT MakeProperty(double value, ABI::Windows::Foundation::IPropertyValue** result)
	{
		auto pv = winrt::Windows::Foundation::PropertyValue::CreateDouble(value);
		pv.as<ABI::Windows::Foundation::IPropertyValue>().copy_to(result);
		return S_OK;
	}

	HRESULT MakeProperty(UINT32 value, ABI::Windows::Foundation::IPropertyValue** result)
	{
		auto pv = winrt::Windows::Foundation::PropertyValue::CreateUInt32(value);
		pv.as<ABI::Windows::Foundation::IPropertyValue>().copy_to(result);
		return S_OK;
	}

	HRESULT MakeProperty(INT32 value, ABI::Windows::Foundation::IPropertyValue** result)
	{
		auto pv = winrt::Windows::Foundation::PropertyValue::CreateInt32(value);
		pv.as<ABI::Windows::Foundation::IPropertyValue>().copy_to(result);
		return S_OK;
	}

	HRESULT MakeProperty(bool value, ABI::Windows::Foundation::IPropertyValue** result)
	{
		auto pv = winrt::Windows::Foundation::PropertyValue::CreateBoolean(value);
		pv.as<ABI::Windows::Foundation::IPropertyValue>().copy_to(result);
		return S_OK;
	}

	HRESULT ReturnSource(winrt::Windows::Graphics::Effects::IGraphicsEffectSource& source, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** outValue)
	{
		if (source)
		{
			source.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(outValue);
			return S_OK;
		}

		return E_FAIL;
	}
}
