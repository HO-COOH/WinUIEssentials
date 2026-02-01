#pragma once
#include <d2d1.h>

struct ID2D1DeviceContext;

class D2D1DeviceContextState
{
	winrt::com_ptr<ID2D1Image> m_originalTarget;
	D2D1::Matrix3x2F m_originalTransform;
	ID2D1DeviceContext* m_d2dContext;
public:
	D2D1DeviceContextState(ID2D1DeviceContext* d2dContext);
	~D2D1DeviceContextState();
};

