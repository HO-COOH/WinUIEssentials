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
#include "TenMicaConstants.h"


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
		switch (msg)
		{
			case WM_WINDOWPOSCHANGING:
			{
				auto* pThis = reinterpret_cast<TenMicaBackdrop*>(dwRefData);
				auto* windowPos = reinterpret_cast<WINDOWPOS const*>(lParam);
				// Only update if position actually changed (not just size or z-order)
				if (!(windowPos->flags & SWP_NOMOVE))
					pThis->updateBrushOffset(windowPos->x, windowPos->y);
				break;
			}
			case WM_DPICHANGED:
			{
				auto* pThis = reinterpret_cast<TenMicaBackdrop*>(dwRefData);
				auto* suggestedRect = reinterpret_cast<RECT const*>(lParam);
				pThis->updateBrushOffset(suggestedRect->left, suggestedRect->top);
				break;
			}
			case WM_ACTIVATE:
			{
				auto const isActive = (LOWORD(wParam) != WA_INACTIVE);
				auto* pThis = reinterpret_cast<TenMicaBackdrop*>(dwRefData);
				pThis->crossFadeBrush.StartAnimation(
					L"CrossFade.CrossFade",
					isActive ? pThis->m_crossFadeForwardAnimation : pThis->m_crossFadeBackwardAnimation
				);
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
        m_bindThemeRevoker = value.ActualThemeChanged(winrt::auto_revoke, [this](winrt::Microsoft::UI::Xaml::FrameworkElement const& sender, auto&&)
        {
            bool isLight = sender.ActualTheme() == winrt::Microsoft::UI::Xaml::ElementTheme::Light;
            onThemeChanged(isLight);
        });
    }

    void TenMicaBackdrop::OnTargetConnected(winrt::Microsoft::UI::Composition::ICompositionSupportsSystemBackdrop const& connectedTarget, winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot)
    {
        auto brush = makeBrush();
        connectedTarget.SystemBackdrop(brush);
		m_hwnd = GetHwnd(xamlRoot);
		RECT windowRect;
		winrt::check_bool(GetWindowRect(m_hwnd, &windowRect));
		updateBrushOffset(windowRect.left, windowRect.top);
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

	void TenMicaBackdrop::createBrush(bool isLightMode)
	{
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, TenMicaConstants::D2D::BlurRadius));
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD));
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY));

		auto baseColor = isLightMode ? TenMicaConstants::D2D::LuminosityColorLight : TenMicaConstants::D2D::LuminosityColorDark;
		winrt::check_hresult(m_luminosityColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));
		winrt::check_hresult(m_luminosityBlendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_LUMINOSITY));

		m_luminosityBlendEffect->SetInputEffect(0, m_blurEffect.get());
		m_luminosityBlendEffect->SetInputEffect(1, m_luminosityColorEffect.get());

		baseColor.a = isLightMode ? TenMicaConstants::D2D::TintColorOpacityLight : TenMicaConstants::D2D::TintColorOpacityDark;
		winrt::check_hresult(m_tintColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));

		winrt::check_hresult(m_finalBlend->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_COLOR));
		m_finalBlend->SetInputEffect(0, m_luminosityBlendEffect.get());
		m_finalBlend->SetInputEffect(1, m_tintColorEffect.get());
	}

	void TenMicaBackdrop::onThemeChanged(bool isLightTheme)
	{
		m_themeCrossFadeBrush.StartAnimation(
			L"ThemeFade.CrossFade",
			isLightTheme ? m_crossFadeForwardAnimation : m_crossFadeBackwardAnimation
		);
	}

	void TenMicaBackdrop::createAnimation()
	{
		auto linearEase = compositor.CreateLinearEasingFunction();

		m_crossFadeForwardAnimation = compositor.CreateScalarKeyFrameAnimation();
		m_crossFadeForwardAnimation.InsertKeyFrame(1.f, 0.f, linearEase);
		m_crossFadeForwardAnimation.Duration(TenMicaConstants::AnimationDuration);

		m_crossFadeBackwardAnimation = compositor.CreateScalarKeyFrameAnimation();
		m_crossFadeBackwardAnimation.InsertKeyFrame(1.f, 1.f, linearEase);
		m_crossFadeBackwardAnimation.Duration(TenMicaConstants::AnimationDuration);
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

		m_virtualScreenX = GetSystemMetrics(SM_XVIRTUALSCREEN);
		m_virtualScreenY = GetSystemMetrics(SM_YVIRTUALSCREEN);

		winrt::Windows::Foundation::Size surfaceSize
		{
			static_cast<float>(GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96)),
			static_cast<float>(GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96))
		};
		auto pixelFormat = winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized;
		auto alphaMode = winrt::Windows::Graphics::DirectX::DirectXAlphaMode::Premultiplied;

		// Create light and dark theme surfaces
		m_lightSurface = graphicsDevice.CreateDrawingSurface(surfaceSize, pixelFormat, alphaMode);
		m_darkSurface = graphicsDevice.CreateDrawingSurface(surfaceSize, pixelFormat, alphaMode);

		//auto const scale = winrt::Windows::Foundation::Numerics::float2::one() / (m_dpi / 96.f);

		auto initSurfaceBrush = [this](auto& brush, auto const& surface) {
			brush = compositor.CreateSurfaceBrush(surface);
			brush.Stretch(winrt::Windows::UI::Composition::CompositionStretch::None);
			brush.HorizontalAlignmentRatio({});
			brush.VerticalAlignmentRatio({});
			brush.Scale({ 1.f, 1.f });
		};
		initSurfaceBrush(m_lightBrush, m_lightSurface);
		initSurfaceBrush(m_darkBrush, m_darkSurface);

		// Theme crossfade: Source1=light, Source2=dark, weight 0=light, 1=dark
		auto themeCrossFadeEffect = winrt::make_self<CrossFadeInterop>();
		themeCrossFadeEffect->CrossFade = 0.0f; // start light
		themeCrossFadeEffect->Name(L"ThemeFade");
		themeCrossFadeEffect->Source1 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Light" };
		themeCrossFadeEffect->Source2 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Dark" };

		m_themeCrossFadeBrush = compositor.CreateEffectFactory(*themeCrossFadeEffect, { L"ThemeFade.CrossFade" }).CreateBrush();
		m_themeCrossFadeBrush.SetSourceParameter(L"Light", m_lightBrush);
		m_themeCrossFadeBrush.SetSourceParameter(L"Dark", m_darkBrush);

		// Active/inactive crossfade
		m_inactiveBrush = compositor.CreateColorBrush(winrt::Windows::UI::ColorHelper::FromArgb(255, 32, 32, 32));

		auto crossFadeEffectInterop = winrt::make_self<CrossFadeInterop>();
		crossFadeEffectInterop->CrossFade = 0.0f;
		crossFadeEffectInterop->Name(L"CrossFade");
		crossFadeEffectInterop->Source1 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Source1" };
		crossFadeEffectInterop->Source2 = winrt::Windows::UI::Composition::CompositionEffectSourceParameter{ L"Source2" };

		crossFadeBrush = compositor.CreateEffectFactory(*crossFadeEffectInterop, { L"CrossFade.CrossFade" }).CreateBrush();
		crossFadeBrush.SetSourceParameter(L"Source1", m_themeCrossFadeBrush);
		crossFadeBrush.SetSourceParameter(L"Source2", m_inactiveBrush);

		draw(m_darkSurface, false);
		m_combinedWallpaper.Reset();
		draw(m_lightSurface, true);


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
		if (!m_lightBrush || !m_hwnd)
			return;

		float const offsetX = static_cast<float>(m_virtualScreenX - windowX);
		float const offsetY = static_cast<float>(m_virtualScreenY - windowY);

		m_lightBrush.Offset({ offsetX, offsetY });
		m_darkBrush.Offset({ offsetX, offsetY });
	}


	void TenMicaBackdrop::draw(winrt::Windows::UI::Composition::CompositionDrawingSurface const& surface, bool isLightMode)
	{
		auto surfaceInterop = surface.as<ABI::Windows::UI::Composition::ICompositionDrawingSurfaceInterop>();

		winrt::com_ptr<ID2D1DeviceContext> d2dContext;
		POINT offset{};
		winrt::check_hresult(surfaceInterop->BeginDraw(nullptr, IID_PPV_ARGS(d2dContext.put()), &offset));
		d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(static_cast<float>(offset.x), static_cast<float>(offset.y)));
		d2dContext->SetUnitMode(D2D1_UNIT_MODE::D2D1_UNIT_MODE_PIXELS);
		auto combinedWallpaper = m_combinedWallpaper.Draw(m_wallpaperManager.Get(), m_wallpaperManager.Position(), d2dContext.get());
		
		if (!m_blurEffect)
			createEffects(d2dContext.get());
		createBrush(isLightMode);
		m_blurEffect->SetInput(0, combinedWallpaper);
		d2dContext->DrawImage(m_finalBlend.get());
		winrt::check_hresult(surfaceInterop->EndDraw());
	}
}
