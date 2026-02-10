#include "pch.h"
#include "CombinedWallpaperSurfaces.h"
#include <windows.ui.composition.interop.h>
#include <d2d1.h>
#include <d3d11.h>
#include "TenMicaConstants.h"

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

void CombinedWallpaperSurfaces::createD2DEffects(ID2D1DeviceContext* d2dContext)
{
	if (m_blurEffect)
		return;

	winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1GaussianBlur, m_blurEffect.put()));
	winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_finalBlend.put()));
	winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, luminosityColorEffect.put()));
	winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, luminosityBlendEffect.put()));
	winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, tintColorEffect.put()));


	winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, TenMicaConstants::D2D::BlurRadius));
	winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD));
	winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY));

	
	winrt::check_hresult(luminosityBlendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_LUMINOSITY));

	luminosityBlendEffect->SetInputEffect(0, m_blurEffect.get());
	luminosityBlendEffect->SetInputEffect(1, luminosityColorEffect.get());

	winrt::check_hresult(m_finalBlend->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_COLOR));
	m_finalBlend->SetInputEffect(0, luminosityBlendEffect.get());
	m_finalBlend->SetInputEffect(1, tintColorEffect.get());
}

winrt::Windows::UI::Composition::CompositionSurfaceBrush CombinedWallpaperSurfaces::initSurfaceBrush(
	winrt::Windows::UI::Composition::Compositor const& compositor,
	winrt::Windows::UI::Composition::CompositionDrawingSurface const& surface
)
{
	auto brush = compositor.CreateSurfaceBrush(surface);
	brush.Stretch(winrt::Windows::UI::Composition::CompositionStretch::None);
	brush.HorizontalAlignmentRatio({});
	brush.VerticalAlignmentRatio({});
	brush.Scale({ 1.f, 1.f });
	return brush;
}

void CombinedWallpaperSurfaces::drawToSurfaceImpl(bool isLight, WallpaperManager& wallpaper)
{
	auto surfaceInterop = (isLight? m_surfaceLight : m_surfaceDark).as<ABI::Windows::UI::Composition::ICompositionDrawingSurfaceInterop>();
	winrt::com_ptr<ID2D1DeviceContext> d2dContext;
	POINT offset{};
	winrt::check_hresult(surfaceInterop->BeginDraw(nullptr, IID_PPV_ARGS(d2dContext.put()), &offset));
	d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(static_cast<float>(offset.x), static_cast<float>(offset.y)));
	d2dContext->SetUnitMode(D2D1_UNIT_MODE::D2D1_UNIT_MODE_PIXELS);
	auto combinedWallpaper = (isLight? m_combinedWallpaperLight : m_combinedWallpaperDark).Draw(wallpaper.Get(), wallpaper.Position(), d2dContext.get());
	createD2DEffects(d2dContext.get());
	setEffectValues(isLight);
	m_blurEffect->SetInput(0, combinedWallpaper);
	d2dContext->DrawImage(m_finalBlend.get());
	winrt::check_hresult(surfaceInterop->EndDraw());
}

void CombinedWallpaperSurfaces::setEffectValues(bool isLight)
{
	auto baseColor = isLight ? TenMicaConstants::D2D::LuminosityColorLight : TenMicaConstants::D2D::LuminosityColorDark;
	winrt::check_hresult(luminosityColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));
	baseColor.a = isLight ? TenMicaConstants::D2D::TintColorOpacityLight : TenMicaConstants::D2D::TintColorOpacityDark;
	winrt::check_hresult(tintColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));
}

winrt::Windows::UI::Composition::CompositionSurfaceBrush CombinedWallpaperSurfaces::DrawToSurfaceWithNewBrush(
    winrt::Windows::UI::Composition::Compositor const& compositor,
	WallpaperManager& wallpaper,
	bool isLight
)
{
	DrawToSurface(compositor, wallpaper, isLight);
	return initSurfaceBrush(compositor, isLight ? m_surfaceLight : m_surfaceDark);
}

void CombinedWallpaperSurfaces::DrawToSurface(winrt::Windows::UI::Composition::Compositor const& compositor, WallpaperManager& wallpaper, bool isLight)
{
	winrt::Windows::Foundation::Size surfaceSize
	{
		static_cast<float>(GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96)),
		static_cast<float>(GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96))
	};

	constexpr static auto pixelFormat = winrt::Windows::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized;
	constexpr static auto alphaMode = winrt::Windows::Graphics::DirectX::DirectXAlphaMode::Premultiplied;

	thread_local auto d2dDevice = GetD2D1Device();

	if (!graphicsDevice)
	{
		auto compositorInterop = compositor.as<ABI::Windows::UI::Composition::ICompositorInterop>();
		winrt::check_hresult(compositorInterop->CreateGraphicsDevice(
			d2dDevice.get(),
			reinterpret_cast<ABI::Windows::UI::Composition::ICompositionGraphicsDevice**>(winrt::put_abi(graphicsDevice))
		));
	}

	if (isLight)
	{
		if (!m_surfaceLight)
			m_surfaceLight = graphicsDevice.CreateDrawingSurface(surfaceSize, pixelFormat, alphaMode);
		drawToSurfaceImpl(true, wallpaper);
	}
	else
	{
		if (!m_surfaceDark)
			m_surfaceDark = graphicsDevice.CreateDrawingSurface(surfaceSize, pixelFormat, alphaMode);
		drawToSurfaceImpl(false, wallpaper);
	}
}
