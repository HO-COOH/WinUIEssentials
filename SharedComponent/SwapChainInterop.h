#pragma once
#include <winrt/base.h>
#include <dxgi1_3.h>

struct ID3D11Device;
struct ID2D1DeviceContext;

class SwapChainInterop : public winrt::com_ptr<IDXGISwapChain1>
{

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
	//UI thread. Returns true if size or scale actually changed and the swap-chain
	//target needs to be recreated on the draw thread.
	[[nodiscard]] bool SizeChanged(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& sender, winrt::WindowsNamespace::UI::Xaml::SizeChangedEventArgs const& arg);
	[[nodiscard]] bool CompositionScaleChanged(winrt::WindowsNamespace::UI::Xaml::Controls::SwapChainPanel const& sender);

	//Draw thread. Resizes back buffers to CurrentSize*Scale, reapplies the
	//inverse-DPI composition transform, and binds a new target bitmap.
	void SetTarget(ID2D1DeviceContext* d2dContext);
	//~SwapChainInterop()
	//{
	//	OutputDebugString(L"Destructed\n");
	//}
};