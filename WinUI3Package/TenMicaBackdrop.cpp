#include "pch.h"
#include "TenMicaBackdrop.h"
#if __has_include("TenMicaBackdrop.g.cpp")
#include "TenMicaBackdrop.g.cpp"
#endif
#include <d3d11.h>
#pragma comment(lib, "dxguid.lib")
#include <windows.ui.composition.interop.h>
#include "CrossFadeEffectInterop.h"
#include "HwndHelper.hpp"


namespace winrt::WinUI3Package::implementation
{
	static auto GetD2D1Device()
	{
		winrt::com_ptr<ID2D1Factory1> d2dFactory;
		D2D1_FACTORY_OPTIONS options{};
		winrt::check_hresult(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(ID2D1Factory1),
			&options,
			d2dFactory.put_void()
		));

		winrt::com_ptr<ID3D11Device> d3dDevice;
		D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
		winrt::check_hresult(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			d3dDevice.put(),
			nullptr,
			nullptr
		));
		auto dxgiDevice = d3dDevice.as<IDXGIDevice>();

		winrt::com_ptr<ID2D1Device> d2dDevice;
		winrt::check_hresult(d2dFactory->CreateDevice(
			dxgiDevice.get(),
			d2dDevice.put()
		));
		return d2dDevice;
	}

	LRESULT CALLBACK TenMicaBackdrop::subclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
	{
		auto* pThis = reinterpret_cast<TenMicaBackdrop*>(dwRefData);

		switch (msg)
		{
			case WM_WINDOWPOSCHANGING:
			{
				//TODO: this is incorrect when dpi changed.
				auto* pos = reinterpret_cast<WINDOWPOS*>(lParam);
				// Only update if position actually changed (not just size or z-order)
				if (!(pos->flags & SWP_NOMOVE))
				{
					// Use the incoming position from WINDOWPOS to update before the move happens
					pThis->updateBrushOffset(pos->x, pos->y);
				}
				break;
			}
			case WM_DPICHANGED:
			{
				// Update DPI and brush scale when moving to a monitor with different DPI
				pThis->m_dpi = HIWORD(wParam);
				//auto const scale = winrt::Windows::Foundation::Numerics::float2::one() / (pThis->m_dpi / 96.f);
				//pThis->m_surfaceBrush.Scale(scale);

				// Update brush offset with new DPI
				auto* suggestedRect = reinterpret_cast<RECT*>(lParam);
				pThis->updateBrushOffset(suggestedRect->left, suggestedRect->top);
				break;
			}
			case WM_ACTIVATE:
			{
				if (LOWORD(wParam) == WA_INACTIVE)
				{
					// Window deactivated - play backward animation (crossfade to solid color)
					pThis->crossFadeBrush.StartAnimation(L"CrossFade.CrossFade", pThis->m_crossFadeBackwardAnimation);
				}
				else
				{
					// Window activated (WA_ACTIVE or WA_CLICKACTIVE) - play forward animation (crossfade to mica)
					pThis->crossFadeBrush.StartAnimation(L"CrossFade.CrossFade", pThis->m_crossFadeForwardAnimation);
				}
				break;
			}
			case WM_NCDESTROY:
				// Remove subclass before window is destroyed
				RemoveWindowSubclass(hwnd, subclassProc, uIdSubclass);
				break;
			}

		return DefSubclassProc(hwnd, msg, wParam, lParam);
	}

    winrt::Microsoft::UI::Xaml::FrameworkElement TenMicaBackdrop::BindThemeTo()
    {
        return m_bindThemeTo.get();
    }

    void TenMicaBackdrop::BindThemeTo(winrt::Microsoft::UI::Xaml::FrameworkElement const value)
    {
        m_bindThemeTo = value;
        m_bindThemeRevoker = value.ActualThemeChanged(winrt::auto_revoke, [this](auto&&...)
            {

            });
    }

    void TenMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
        auto brush = makeBrush();
        connectedTarget.SystemBackdrop(brush);
		m_hwnd = GetHwnd(xamlRoot);
		SetWindowSubclass(m_hwnd, subclassProc, 0, reinterpret_cast<DWORD_PTR>(this));
    }

	void TenMicaBackdrop::OnTargetDisconnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget)
	{
		RemoveWindowSubclass(m_hwnd, subclassProc, 0);
	}

    void TenMicaBackdrop::createEffects(ID2D1DeviceContext* d2dContext)
    {
        winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1GaussianBlur, m_blurEffect.put()));
        winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, m_luminosityColorEffect.put()));
        winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_luminosityBlendEffect.put()));
        winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, m_tintColorEffect.put()));
        winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_finalBlend.put()));
    }

	void TenMicaBackdrop::createBrush(ID2D1DeviceContext* d2dContext)
	{
		constexpr bool isLightMode = false;

		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 120.f)); // Debug blur
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD));
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY));

		D2D1_COLOR_F baseColor = isLightMode ? D2D1_COLOR_F{ 0.9529f, 0.9529f, 0.9529f, 1.0f } : D2D1_COLOR_F{ 0.125f, 0.125f, 0.125f, 1.0f };
		winrt::check_hresult(m_luminosityColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));
		winrt::check_hresult(m_luminosityBlendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_LUMINOSITY));

		m_luminosityBlendEffect->SetInputEffect(0, m_blurEffect.get());
		m_luminosityBlendEffect->SetInputEffect(1, m_luminosityColorEffect.get());

		baseColor.a = isLightMode ? 0.5f : 0.8f;
		winrt::check_hresult(m_tintColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));

		winrt::check_hresult(m_finalBlend->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_COLOR));
		m_finalBlend->SetInputEffect(0, m_luminosityBlendEffect.get());
		m_finalBlend->SetInputEffect(1, m_tintColorEffect.get());
	}

	void TenMicaBackdrop::createAnimation()
	{
		m_crossFadeForwardAnimation = compositor.CreateScalarKeyFrameAnimation();
		auto linearEase = compositor.CreateLinearEasingFunction();
		m_crossFadeForwardAnimation.InsertKeyFrame(0.f, 1.f, linearEase);
		m_crossFadeForwardAnimation.InsertKeyFrame(1.f, 0.f, linearEase);
		m_crossFadeBackwardAnimation = compositor.CreateScalarKeyFrameAnimation();
		m_crossFadeBackwardAnimation.InsertKeyFrame(0.f, 0.f, linearEase);
		m_crossFadeBackwardAnimation.InsertKeyFrame(1.f, 1.f, linearEase);
	}

    winrt::Windows::UI::Composition::CompositionBrush TenMicaBackdrop::makeBrush()
    {
		compositor = {};
		auto compositorInterop = compositor.as<ABI::Windows::UI::Composition::ICompositorInterop>();

		winrt::Windows::UI::Composition::CompositionGraphicsDevice graphicsDevice{ nullptr };
		winrt::check_hresult(compositorInterop->CreateGraphicsDevice(
			GetD2D1Device().get(),
			reinterpret_cast<ABI::Windows::UI::Composition::ICompositionGraphicsDevice**>(winrt::put_abi(graphicsDevice))
		));


		auto sizeX = GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96);
		auto sizeXOrig = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		m_drawingSurface = graphicsDevice.CreateDrawingSurface(
			winrt::Windows::Foundation::Size
			{
				static_cast<float>(GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96)),
				static_cast<float>(GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96))
			},
			winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized,
			winrt::Windows::Graphics::DirectX::DirectXAlphaMode::Premultiplied
		);
		m_surfaceBrush = compositor.CreateSurfaceBrush(m_drawingSurface);
		m_surfaceBrush.Stretch(winrt::Windows::UI::Composition::CompositionStretch::None);
		//top left align the brush
		m_surfaceBrush.HorizontalAlignmentRatio({});
		m_surfaceBrush.VerticalAlignmentRatio({});

		auto const scale = winrt::Windows::Foundation::Numerics::float2::one() / (m_dpi / 96.f);
		m_surfaceBrush.Scale(scale);


		auto solidColorTintBrush = compositor.CreateColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(255, 32, 32, 32));

		auto crossFadeEffectInterop = winrt::make_self<CrossFadeInterop>();
		crossFadeEffectInterop->CrossFade = 0.0f;
		crossFadeEffectInterop->Name(L"CrossFade");
		crossFadeEffectInterop->Source1 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Source1" };
		crossFadeEffectInterop->Source2 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Source2" };

		crossFadeBrush = compositor.CreateEffectFactory(*crossFadeEffectInterop, { L"CrossFade.CrossFade" }).CreateBrush();
		crossFadeBrush.SetSourceParameter(L"Source1", m_surfaceBrush);
		crossFadeBrush.SetSourceParameter(L"Source2", solidColorTintBrush);

		draw();
		createAnimation();

		return crossFadeBrush;
    }

	void TenMicaBackdrop::updateBrushOffset()
	{
		if (!m_hwnd)
			return;

		RECT windowRect{};
		GetWindowRect(m_hwnd, &windowRect);
		updateBrushOffset(windowRect.left, windowRect.top);
	}

	void TenMicaBackdrop::updateBrushOffset(int windowX, int windowY)
	{
		if (!m_surfaceBrush || !m_hwnd)
			return;

		// Convert from physical pixels to DIPs (the brush offset is in DIPs before scaling)
		float offsetX = -static_cast<float>(windowX);
		float offsetY = -static_cast<float>(windowY);

		m_surfaceBrush.Offset({ offsetX, offsetY });
	}


	void TenMicaBackdrop::draw()
	{
		auto surfaceInterop = m_drawingSurface.as<ABI::Windows::UI::Composition::ICompositionDrawingSurfaceInterop>();

		winrt:com_ptr<ID2D1DeviceContext> d2dContext;
		POINT offset{};
		winrt::check_hresult(surfaceInterop->BeginDraw(nullptr, IID_PPV_ARGS(d2dContext.put()), &offset));
		d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(static_cast<float>(offset.x), static_cast<float>(offset.y)));
		d2dContext->SetUnitMode(D2D1_UNIT_MODE::D2D1_UNIT_MODE_PIXELS);
		auto combinedWallpaper = m_combinedWallpaper.Draw(m_wallpaperManager.Get(), m_wallpaperManager.Position(), d2dContext.get());
		if (!m_blurEffect)
		{
			createEffects(d2dContext.get());
			createBrush(d2dContext.get());
		}
		m_blurEffect->SetInput(0, combinedWallpaper);
		d2dContext->Clear(D2D1::ColorF{ D2D1::ColorF::Red });
		d2dContext->DrawImage(m_finalBlend.get());
		//TODO: debug
		//d2dContext->DrawImage(m_blurEffect.get());
		winrt::check_hresult(surfaceInterop->EndDraw());
	}
}
