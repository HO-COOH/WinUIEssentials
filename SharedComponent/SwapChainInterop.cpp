#include "pch.h"
#include "SwapChainInterop.h"
#include <d3d11.h>
#include <d2d1_1.h>

#if defined Build_WinUIPackage
#include <microsoft.ui.xaml.media.dxinterop.h>
#else
#include <windows.ui.xaml.media.dxinterop.h>
#endif

void SwapChainInterop::SizeChanged(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& sender, winrt::WindowsNamespace::UI::Xaml::SizeChangedEventArgs const& arg)
{
	auto const newSize = arg.NewSize();
	if (newSize == CurrentSize)
		return;
	
	CurrentSize = newSize;
	Scale = sender.CompositionScaleX();
	get() ? resize(sender) : create(sender);
}

void SwapChainInterop::SetTarget(ID2D1DeviceContext* d2dContext)
{
	winrt::com_ptr<IDXGISurface> dxgiSurface;
	winrt::check_hresult(get()->GetBuffer(0, __uuidof(IDXGISurface), dxgiSurface.put_void()));

	D2D1_BITMAP_PROPERTIES1 property
	{
		.pixelFormat =
		{
			.format = DXGI_FORMAT_B8G8R8A8_UNORM,
			.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED
		},
		.dpiX = 96.0f,
		.dpiY = 96.0f,
		.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW
	};

	winrt::com_ptr<ID2D1Bitmap1> targetBitmap;
	winrt::check_hresult(d2dContext->CreateBitmapFromDxgiSurface(dxgiSurface.get(), &property, targetBitmap.put()));
	d2dContext->SetTarget(targetBitmap.get());
	d2dContext->SetDpi(96.0f, 96.0f);
}

void SwapChainInterop::resize(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel)
{
}

void SwapChainInterop::create(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel)
{
	auto const rawWidth = (std::max<UINT>)(1, static_cast<UINT>(CurrentSize.Width * Scale));
	auto const rawHeight = (std::max<UINT>)(1, static_cast<UINT>(CurrentSize.Height * Scale));
	DXGI_SWAP_CHAIN_DESC1 const swapChainDesc
	{
		.Width = rawWidth,
		.Height = rawHeight,
		.Format = DXGI_FORMAT_B8G8R8A8_UNORM,
		.SampleDesc =
		{
			.Count = 1
		},
		.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
		.BufferCount = 2,
		.Scaling = DXGI_SCALING_STRETCH,
		.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		.AlphaMode = DXGI_ALPHA_MODE_PREMULTIPLIED
	};
	winrt::check_hresult(dxgiFactory->CreateSwapChainForComposition(m_d3d11Device, &swapChainDesc, nullptr, put()));
	swapChainPanel.as<ISwapChainPanelNative>()->SetSwapChain(get());
	
	inverseDpi();
}

void SwapChainInterop::inverseDpi()
{
	auto swapChain2 = as<IDXGISwapChain2>();
	auto const inverseScaleMatrix = createScaleMatrix(1.0f / Scale);
	winrt::check_hresult(swapChain2->SetMatrixTransform(&inverseScaleMatrix));
}

void SwapChainInterop::Set(ID3D11Device* d3d11Device, winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel)
{
	winrt::com_ptr<IDXGIDevice> dxgiDevice;
	winrt::check_hresult(d3d11Device->QueryInterface(dxgiDevice.put()));
	winrt::com_ptr<IDXGIAdapter> dxgiAdapter;
	winrt::check_hresult(dxgiDevice->GetAdapter(dxgiAdapter.put()));

	winrt::check_hresult(dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), dxgiFactory.put_void()));
	m_d3d11Device = d3d11Device;
}
