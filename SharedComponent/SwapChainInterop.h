#pragma once
#include <winrt/base.h>
#include <dxgi1_3.h>

struct ID3D11Device;
struct ID2D1DeviceContext;

class SwapChainInterop : public winrt::com_ptr<IDXGISwapChain1>
{

	void resize(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel);
	void create(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel);

	ID3D11Device* m_d3d11Device{};
	winrt::com_ptr<IDXGIFactory2> dxgiFactory;

	void inverseDpi();

	constexpr static auto createScaleMatrix(float scale)
	{
		return DXGI_MATRIX_3X2_F
		{
			._11 = scale,
			._22 = scale
		};
	}
public:
	float Scale = 1.0f;
	winrt::Windows::Foundation::Size CurrentSize{};
	
	SwapChainInterop() = default;
	void Set(ID3D11Device* d3d11Device, winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& swapChainPanel);
	void SizeChanged(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& sender, winrt::WindowsNamespace::UI::Xaml::SizeChangedEventArgs const& arg);

	void SetTarget(ID2D1DeviceContext* d2dContext);
	//~SwapChainInterop()
	//{
	//	OutputDebugString(L"Destructed\n");
	//}
};