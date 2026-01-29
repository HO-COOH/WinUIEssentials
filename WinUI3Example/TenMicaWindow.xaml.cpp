#include "pch.h"
#include "TenMicaWindow.xaml.h"
#if __has_include("TenMicaWindow.g.cpp")
#include "TenMicaWindow.g.cpp"
#endif
#include <d3d11.h>
#include <d2d1_1.h>
#include <winrt/Microsoft.UI.Composition.Interop.h>
#include <HwndHelper.hpp>
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


		auto sizeX = GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96);
		auto sizeXOrig = GetSystemMetrics(SM_CXVIRTUALSCREEN);
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
		//top left align the brush
		brush.HorizontalAlignmentRatio({});
		brush.VerticalAlignmentRatio({});
		auto sprite = compositor.CreateSpriteVisual();
		sprite.Brush(brush);
		auto spriteSizeExpression = compositor.CreateExpressionAnimation(L"host.Size");
		spriteSizeExpression.SetReferenceParameter(L"host", visual);
		sprite.StartAnimation(L"Size", spriteSizeExpression);
		winrt::Microsoft::UI::Xaml::Hosting::ElementCompositionPreview::SetElementChildVisual(CompositionHost(), sprite);
		auto const dpi = GetDpiForWindow(GetHwnd(*this));
		auto const scale = winrt::Windows::Foundation::Numerics::float2::one() / (dpi / 96.f);
		brush.Scale(scale);
		Draw();
	}

	void TenMicaWindow::Draw()
	{
		auto surfaceInterop = m_drawingSurface.as<winrt::Microsoft::UI::Composition::ICompositionDrawingSurfaceInterop>();
		
		winrt:com_ptr<ID2D1DeviceContext> d2dContext;
		POINT offset{};
		winrt::check_hresult(surfaceInterop->BeginDraw(nullptr, IID_PPV_ARGS(d2dContext.put()), &offset));
		d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(static_cast<float>(offset.x), static_cast<float>(offset.y)));
		d2dContext->SetUnitMode(D2D1_UNIT_MODE::D2D1_UNIT_MODE_PIXELS);
		if (!m_blurEffect)
			createBrush(d2dContext.get());
		d2dContext->Clear(D2D1::ColorF{ D2D1::ColorF::Red });
		d2dContext->DrawImage(m_finalBlend.get());
		//TODO: debug
		//d2dContext->DrawImage(m_blurEffect.get());
		winrt::check_hresult(surfaceInterop->EndDraw());
	}

	void TenMicaWindow::createBrush(ID2D1DeviceContext* d2dContext)
	{
		constexpr bool isLightMode = false;
		createEffects(d2dContext);
		combinedWallpaper(d2dContext);
		auto wallpaperSize = wallpaperBitmap->GetSize();
		auto size = m_drawingSurface.Size();
		auto scaleX = size.Width / wallpaperSize.width;
		auto scaleY = size.Height / wallpaperSize.height;
		auto scale = (std::max)(scaleX, scaleY);

		m_scaleEffect->SetInput(0, wallpaperBitmap.get());
		winrt::check_hresult(m_scaleEffect->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F(scale, scale)));

		// --- Blur ---
		m_blurEffect->SetInputEffect(0, m_scaleEffect.get());
		winrt::check_hresult(m_blurEffect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 0.f)); // Debug blur
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
		m_finalBlend->SetInputEffect(0, m_luminosityBlendEffect.get());
		m_finalBlend->SetInputEffect(1, m_tintColorEffect.get());
	}

	[[nodiscard]] static auto swapTarget(ID2D1DeviceContext* d2dContext, ID2D1Bitmap* newTarget)
	{
		winrt::com_ptr<ID2D1Image> originalTarget;
		d2dContext->GetTarget(originalTarget.put());
		d2dContext->SetTarget(newTarget);
		return originalTarget;
	}

	void TenMicaWindow::createEffects(ID2D1DeviceContext* d2dContext)
	{
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Scale, m_scaleEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1GaussianBlur, m_blurEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, m_luminosityColorEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_luminosityBlendEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Flood, m_tintColorEffect.put()));
		winrt::check_hresult(d2dContext->CreateEffect(CLSID_D2D1Blend, m_finalBlend.put()));
	}

	static void drawToCombinedWallpaperBitmap(
		ID2D1DeviceContext* d2dContext,
		WallpaperInfo const& wallpaperInfo,
		DESKTOP_WALLPAPER_POSITION mode,
		ID2D1Bitmap1* combinedBitmap)
	{
		winrt::com_ptr<ID2D1Bitmap1> wallpaperBitmap;

		//Todo: if size if weird, use another overload
		winrt::check_hresult(d2dContext->CreateBitmapFromWicBitmap(wallpaperInfo.wallpaper.get(), wallpaperBitmap.put()));

		auto const drawBitmapImpl = [&d2dContext, &wallpaperBitmap](D2D1_RECT_F rect) 
		{
			d2dContext->DrawBitmap(wallpaperBitmap.get(), rect);
		};

		switch (mode)
		{
			case DESKTOP_WALLPAPER_POSITION::DWPOS_CENTER:
			{
				auto const wallpaperSize = wallpaperBitmap->GetPixelSize();
				auto const left = (std::min<float>)(wallpaperInfo.rect.left, (wallpaperInfo.rect.right + wallpaperInfo.rect.left - wallpaperSize.width) / 2);
				auto const right = (std::max<float>)(wallpaperInfo.rect.right, (wallpaperInfo.rect.right + wallpaperInfo.rect.left + wallpaperSize.width) / 2);
				auto const top = (std::min<float>)(wallpaperInfo.rect.top, (wallpaperInfo.rect.top + wallpaperInfo.rect.bottom - wallpaperSize.height) / 2);
				auto const bottom = (std::max<float>)(wallpaperInfo.rect.bottom, (wallpaperInfo.rect.top + wallpaperInfo.rect.bottom - wallpaperSize.height) / 2);
				drawBitmapImpl(D2D1::RectF(left, top, right, bottom));
				break;
			}
			case DESKTOP_WALLPAPER_POSITION::DWPOS_TILE:
			{
				winrt::com_ptr<ID2D1BitmapBrush> tileBrush;
				winrt::check_hresult(d2dContext->CreateBitmapBrush(wallpaperBitmap.get(), tileBrush.put()));
				tileBrush->SetExtendModeX(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_WRAP);
				tileBrush->SetExtendModeY(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_WRAP);
				tileBrush->SetTransform(D2D1::Matrix3x2F::Translation(wallpaperInfo.rect.left, wallpaperInfo.rect.top));
				d2dContext->FillRectangle(D2D1::RectF(wallpaperInfo.rect.left, wallpaperInfo.rect.top, wallpaperInfo.rect.right, wallpaperInfo.rect.bottom), tileBrush.get());
				break;
			}
			case DESKTOP_WALLPAPER_POSITION::DWPOS_STRETCH:
			{
				drawBitmapImpl(D2D1::RectF(wallpaperInfo.rect.left, wallpaperInfo.rect.top, wallpaperInfo.rect.right, wallpaperInfo.rect.bottom));
				break;
			}
			case DESKTOP_WALLPAPER_POSITION::DWPOS_FIT:
			{
				auto const wallpaperSize = wallpaperBitmap->GetPixelSize();
				auto const rectWidth = static_cast<float>(wallpaperInfo.rect.right - wallpaperInfo.rect.left);
				auto const rectHeight = static_cast<float>(wallpaperInfo.rect.bottom - wallpaperInfo.rect.top);

				auto const scaleX = rectWidth / wallpaperSize.width;
				auto const scaleY = rectHeight / wallpaperSize.height;
				auto const finalScale = (std::min)(scaleX, scaleY);

				auto const destWidth = wallpaperSize.width * finalScale;
				auto const destHeight = wallpaperSize.height * finalScale;

				auto const destLeft = wallpaperInfo.rect.left + (rectWidth - destWidth) / 2.0f;
				auto const destTop = wallpaperInfo.rect.top + (rectHeight - destHeight) / 2.0f;

				drawBitmapImpl(D2D1::RectF(destLeft, destTop, destLeft + destWidth, destTop + destHeight));
				break;
			}
			case DESKTOP_WALLPAPER_POSITION::DWPOS_FILL:
			{
				auto const wallpaperSize = wallpaperBitmap->GetPixelSize();
				auto const rectWidth = static_cast<float>(wallpaperInfo.rect.right - wallpaperInfo.rect.left);
				auto const rectHeight = static_cast<float>(wallpaperInfo.rect.bottom - wallpaperInfo.rect.top);

				auto const scaleX = rectWidth / wallpaperSize.width;
				auto const scaleY = rectHeight / wallpaperSize.height;
				auto const finalScale = (std::max)(scaleX, scaleY);

				auto const destWidth = wallpaperSize.width * finalScale;
				auto const destHeight = wallpaperSize.height * finalScale;

				auto const destLeft = wallpaperInfo.rect.left + (rectWidth - destWidth) / 2.0f;
				auto const destTop = wallpaperInfo.rect.top + (rectHeight - destHeight) / 2.0f;

				d2dContext->PushAxisAlignedClip(
					D2D1::RectF(
						static_cast<float>(wallpaperInfo.rect.left),
						static_cast<float>(wallpaperInfo.rect.top),
						static_cast<float>(wallpaperInfo.rect.right),
						static_cast<float>(wallpaperInfo.rect.bottom)
					),
					D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
				);

				drawBitmapImpl(D2D1::RectF(destLeft, destTop, destLeft + destWidth, destTop + destHeight));

				d2dContext->PopAxisAlignedClip();
				break;
			}
			case DESKTOP_WALLPAPER_POSITION::DWPOS_SPAN:
			{
				float width = static_cast<float>(GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96));
				float height = static_cast<float>(GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96));

				auto const wallpaperSize = wallpaperBitmap->GetPixelSize();
				auto const scaleX = width / wallpaperSize.width;
				auto const scaleY = height / wallpaperSize.height;
				auto const finalScale = (std::max)(scaleX, scaleY);

				auto const destWidth = wallpaperSize.width * finalScale;
				auto const destHeight = wallpaperSize.height * finalScale;

				auto const destLeft = (width - destWidth) / 2.0f;
				auto const destTop = (height - destHeight) / 2.0f;

				drawBitmapImpl(D2D1::RectF(destLeft, destTop, destLeft + destWidth, destTop + destHeight));
				break;
			}
		}
	}

	void TenMicaWindow::combinedWallpaper(ID2D1DeviceContext* d2dContext)
	{
		auto combinedWallpaperProperties = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS::D2D1_BITMAP_OPTIONS_TARGET,
			D2D1::PixelFormat(DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE::D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
		winrt::check_hresult(d2dContext->CreateBitmap(
			D2D1::SizeU(
				GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96),
				GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96)
			),
			nullptr,
			0,
			&combinedWallpaperProperties,
			wallpaperBitmap.put()
		));

		auto originalTarget = swapTarget(d2dContext, wallpaperBitmap.get());

		D2D1::Matrix3x2F originalTransform;
		d2dContext->GetTransform(&originalTransform);

		float minX = static_cast<float>(GetSystemMetricsForDpi(SM_XVIRTUALSCREEN, 96));
		float minY = static_cast<float>(GetSystemMetricsForDpi(SM_YVIRTUALSCREEN, 96));
		d2dContext->SetTransform(D2D1::Matrix3x2F::Translation(-minX, -minY));

		d2dContext->Clear(D2D1::ColorF{ 0.0f, 0.0f, 0.0f, 1.0f });

		auto const wallpaperStrechMode = m_wallpaperManager.Position();

		if (wallpaperStrechMode == DESKTOP_WALLPAPER_POSITION::DWPOS_SPAN)
		{
			auto wallpapers = m_wallpaperManager.Get();
			if (!wallpapers.empty())
			{
				drawToCombinedWallpaperBitmap(
					d2dContext,
					wallpapers[0],
					wallpaperStrechMode,
					wallpaperBitmap.get()
				);
			}
		}
		else
		{
			for (auto const& wallpaper : m_wallpaperManager.Get())
			{
				drawToCombinedWallpaperBitmap(
					d2dContext,
					wallpaper,
					wallpaperStrechMode,
					wallpaperBitmap.get()
				);
			}
		}
		
		d2dContext->SetTarget(originalTarget.get());
		d2dContext->SetTransform(originalTransform);
	}
}
