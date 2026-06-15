#pragma once
#include <d3d11.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <winrt/base.h>

namespace DirectN
{
	winrt::com_ptr<ID3D11Device> CreateD3D11Device();
	winrt::com_ptr<ID2D1Device> GetD2D1Device(ID2D1Factory1* d2dFactory, ID3D11Device* d3d11Device);
	winrt::com_ptr<ID2D1Device> GetD2D1Device(ID2D1Factory* d2dFactory, IDXGIDevice* dxgiDevice);

	template<typename DWriteFactory = IDWriteFactory>
	winrt::com_ptr<DWriteFactory> CreateDWriteFactory()
	{
		winrt::com_ptr<DWriteFactory> dwriteFactory;
		winrt::check_hresult(DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(DWriteFactory),
			reinterpret_cast<IUnknown**>(dwriteFactory.put_void())
		));
		return dwriteFactory;
	}
	
	template<typename D2DFactory = ID2D1Factory1>
	winrt::com_ptr<D2DFactory> CreateD2D1Factory()
	{
		winrt::com_ptr<D2DFactory> d2dFactory;
		winrt::check_hresult(D2D1CreateFactory(
			D2D1_FACTORY_TYPE::D2D1_FACTORY_TYPE_SINGLE_THREADED,
			__uuidof(D2DFactory),
			nullptr,
			reinterpret_cast<void**>(d2dFactory.put_void())
		));
		return d2dFactory;
	}
}