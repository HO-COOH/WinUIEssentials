#include "pch.h"
#include "HostBackdrop.h"
#if __has_include("HostBackdrop.g.cpp")
#include "HostBackdrop.g.cpp"
#endif
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.Foundation.h>
#include <windows.graphics.effects.interop.h>
#include <d2d1effects.h>

namespace
{
	struct GaussianBlurEffect : winrt::implements<
		GaussianBlurEffect,
		winrt::Windows::Graphics::Effects::IGraphicsEffect,
		winrt::Windows::Graphics::Effects::IGraphicsEffectSource,
		ABI::Windows::Graphics::Effects::IGraphicsEffectD2D1Interop>
	{
		float BlurAmount{ 9.0f };
		winrt::Windows::Graphics::Effects::IGraphicsEffectSource Source{ nullptr };

		winrt::hstring Name() { return m_name; }
		void Name(winrt::hstring const& value) { m_name = value; }

		IFACEMETHODIMP GetEffectId(GUID* id) noexcept override
		{
			*id = CLSID_D2D1GaussianBlur;
			return S_OK;
		}

		IFACEMETHODIMP GetNamedPropertyMapping(
			LPCWSTR,
			UINT*,
			ABI::Windows::Graphics::Effects::GRAPHICS_EFFECT_PROPERTY_MAPPING*) noexcept override
		{
			return E_INVALIDARG;
		}

		IFACEMETHODIMP GetPropertyCount(UINT* count) noexcept override
		{
			*count = 3;
			return S_OK;
		}

		IFACEMETHODIMP GetProperty(UINT index, ABI::Windows::Foundation::IPropertyValue** value) noexcept override
		{
			winrt::Windows::Foundation::IPropertyValue pv{ nullptr };
			switch (index)
			{
				case D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION:
					pv = winrt::Windows::Foundation::PropertyValue::CreateSingle(BlurAmount).as<winrt::Windows::Foundation::IPropertyValue>();
					break;
				case D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION:
					pv = winrt::Windows::Foundation::PropertyValue::CreateUInt32(D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED).as<winrt::Windows::Foundation::IPropertyValue>();
					break;
				case D2D1_GAUSSIANBLUR_PROP_BORDER_MODE:
					pv = winrt::Windows::Foundation::PropertyValue::CreateUInt32(D2D1_BORDER_MODE_HARD).as<winrt::Windows::Foundation::IPropertyValue>();
					break;
				default:
					return E_INVALIDARG;
			}
			pv.as<ABI::Windows::Foundation::IPropertyValue>().copy_to(value);
			return S_OK;
		}

		IFACEMETHODIMP GetSource(UINT index, ABI::Windows::Graphics::Effects::IGraphicsEffectSource** source) noexcept override
		{
			if (index != 0 || !Source)
				return E_FAIL;
			Source.as<ABI::Windows::Graphics::Effects::IGraphicsEffectSource>().copy_to(source);
			return S_OK;
		}

		IFACEMETHODIMP GetSourceCount(UINT* count) noexcept override
		{
			*count = 1;
			return S_OK;
		}

	private:
		winrt::hstring m_name;
	};
}

namespace winrt::WinUI3Package::implementation
{
	void HostBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
	{
		winrt::Windows::UI::Composition::Compositor compositor;
		auto hostBackdropBrush = compositor.CreateHostBackdropBrush();

		auto blurEffect = winrt::make_self<GaussianBlurEffect>();
		blurEffect->BlurAmount = 60.0f;
		blurEffect->Source = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Backdrop" };

		auto effectFactory = compositor.CreateEffectFactory(*blurEffect);
		auto effectBrush = effectFactory.CreateBrush();
		effectBrush.SetSourceParameter(L"Backdrop", hostBackdropBrush);

		connectedTarget.SystemBackdrop(effectBrush);
	}

	void HostBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
	}
}
