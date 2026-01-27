#include "pch.h"
#include "TenMicaWindow.xaml.h"
#if __has_include("TenMicaWindow.g.cpp")
#include "TenMicaWindow.g.cpp"
#endif
#include <d3d11.h>
#include <d2d1_1.h>
#include <winrt/Microsoft.UI.Composition.Interop.h>

#pragma comment(lib, "dxguid.lib")
// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Example::implementation
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

	TenMicaWindow::TenMicaWindow()
	{
		InitializeComponent();
		auto visual = winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::GetElementVisual(CompositionHost());
		auto compositor = visual.Compositor();
		auto compositorInterop = compositor.as<winrt::Microsoft::UI::Composition::ICompositorInterop>();

		winrt::Microsoft::UI::Composition::CompositionGraphicsDevice graphicsDevice{ nullptr };
		winrt::check_hresult(compositorInterop->CreateGraphicsDevice(
			GetD2D1Device().get(),
			&graphicsDevice
		));

		m_drawingSurface = graphicsDevice.CreateDrawingSurface(
			winrt::Windows::Foundation::Size
			{
				static_cast<float>(GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96)),
				static_cast<float>(GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96))
			},
			winrt::Microsoft::Graphics::DirectX::DirectXPixelFormat::B8G8R8A8UIntNormalized,
			winrt::Microsoft::Graphics::DirectX::DirectXAlphaMode::Premultiplied
		);
		auto brush = compositor.CreateSurfaceBrush(m_drawingSurface);
		brush.Stretch(winrt::Microsoft::UI::Composition::CompositionStretch::None);
		auto sprite = compositor.CreateSpriteVisual();
		sprite.Brush(brush);
		auto spriteSizeExpression = compositor.CreateExpressionAnimation(L"host.Size");
		spriteSizeExpression.SetReferenceParameter(L"host", visual);
		sprite.StartAnimation(L"Size", spriteSizeExpression);
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(CompositionHost(), sprite);
		Draw();
	}

	void TenMicaWindow::Draw()
	{
		auto surfaceInterop = m_drawingSurface.as<winrt::Microsoft::UI::Composition::ICompositionDrawingSurfaceInterop>();
		
		winrt:com_ptr<ID2D1DeviceContext> d2dContext;
		POINT offset{};
		winrt::check_hresult(surfaceInterop->BeginDraw(nullptr, IID_PPV_ARGS(d2dContext.put()), &offset));
		d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(static_cast<float>(offset.x), static_cast<float>(offset.y)));
		if (!m_blurEffect)
			createBrush(d2dContext.get());
		d2dContext->Clear(D2D1::ColorF{ D2D1::ColorF::Red });
		d2dContext->DrawImage(m_finalBlend.get());
		winrt::check_hresult(surfaceInterop->EndDraw());
	}

	void TenMicaWindow::createBrush(ID2D1DeviceContext* d2dContext)
	{
		constexpr bool isLightMode = false;

		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Scale, m_scaleEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1GaussianBlur, m_blurEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, m_luminosityColorEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_luminosityBlendEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, m_tintColorEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_finalBlend.put()));

		// --- Setup Wallpaper & Scaling ---
		auto wallpaper = m_wallpaperManager.Get();
		winrt::com_ptr<ID2D1Bitmap1> wallpaperBitmap;
		
		// FIX: Force 96 DPI to ensure pixel-to-pixel scaling calculations
		D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_NONE,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_UNKNOWN),
			96.0f, 96.0f
		);
		winrt::check_hresult(d2dContext->CreateBitmapFromWicBitmap(wallpaper.get(), &props, wallpaperBitmap.put()));

		auto wallpaperSize = wallpaperBitmap->GetSize();
		auto size = m_drawingSurface.Size();
		auto scaleX = size.Width / wallpaperSize.width;
		auto scaleY = size.Height / wallpaperSize.height;
		auto scale = (std::max)(scaleX, scaleY);

		m_scaleEffect->SetInput(0, wallpaperBitmap.get());
		winrt::check_hresult(m_scaleEffect->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(scale, scale)));

		// FIX: Use Cubic interpolation to prevent the "wavy" moire patterns
		winrt::check_hresult(m_scaleEffect->SetValue(D2D1_SCALE_PROP_INTERPOLATION_MODE, D2D1_SCALE_INTERPOLATION_MODE_HIGH_QUALITY_CUBIC));

		// --- Blur ---
		m_blurEffect->SetInputEffect(0, m_scaleEffect.get());
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 70.f)); // Debug blur
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, D2D1_BORDER_MODE_HARD));
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION, D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY));

		D2D1_COLOR_F baseColor = isLightMode ? D2D1_COLOR_F{ 0.9529f, 0.9529f, 0.9529f, 1.0f } : D2D1_COLOR_F{ 0.125f, 0.125f, 0.125f, 1.0f };
		winrt::check_hresult(m_luminosityColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));

		winrt::check_hresult(m_luminosityBlendEffect->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_LUMINOSITY));

		m_luminosityBlendEffect->SetInputEffect(0, m_blurEffect.get());
		m_luminosityBlendEffect->SetInputEffect(1, m_luminosityColorEffect.get());

		// --- Blend 2: Tint (Luminosity Mode) ---
		baseColor.a = isLightMode? 0.5f : 0.8f; // 50% Opacity for Light Mode
		winrt::check_hresult(m_tintColorEffect->SetValue(D2D1_FLOOD_PROP_COLOR, baseColor));

		winrt::check_hresult(m_finalBlend->SetValue(D2D1_BLEND_PROP_MODE, D2D1_BLEND_MODE_COLOR));
		// Input 0 (Background/Dest) = Tint Color
		// Input 1 (Foreground/Source) = Grayscale Wallpaper
		// Result: Hue/Sat of Dest (Tint) + Lum of Source (Wallpaper) = Tinted Mica
		m_finalBlend->SetInputEffect(0, m_luminosityBlendEffect.get());
		m_finalBlend->SetInputEffect(1, m_tintColorEffect.get());
	}
}
