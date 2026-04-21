#include "pch.h"
#include "DirectN.h"

namespace DirectN
{
	winrt::com_ptr<ID3D11Device> CreateD3D11Device()
	{
		winrt::com_ptr<ID3D11Device> d3dDevice;
		D3D_FEATURE_LEVEL featureLevels[]
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_10_1
		};
		winrt::check_hresult(D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			featureLevels,
			std::size(featureLevels),
			D3D11_SDK_VERSION,
			d3dDevice.put(),
			nullptr,
			nullptr
		));
		return d3dDevice;
	}

	winrt::com_ptr<ID2D1Device> GetD2D1Device(ID2D1Factory1* d2dFactory, ID3D11Device* d3d11Device)
	{
		winrt::com_ptr<ID2D1Device> d2dDevice;
		winrt::com_ptr<IDXGIDevice> dxgiDevice;
		winrt::check_hresult(d3d11Device->QueryInterface(dxgiDevice.put()));
		winrt::check_hresult(d2dFactory->CreateDevice(
			dxgiDevice.get(),
			d2dDevice.put()
		));
		return d2dDevice;
	}

	winrt::com_ptr<IDWriteFactory> CreateDWriteFactory()
	{
		winrt::com_ptr<IDWriteFactory> dwriteFactory;
		winrt::check_hresult(DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(dwriteFactory.put_void())
		));
		return dwriteFactory;
	}

	winrt::com_ptr<ID2D1Device> GetD2D1Device(ID2D1Factory1* d2dFactory, IDXGIDevice* dxgiDevice)
	{
		winrt::com_ptr<ID2D1Device> d2dDevice;
		winrt::check_hresult(d2dFactory->CreateDevice(dxgiDevice, d2dDevice.put()));
		return d2dDevice;
	}
}