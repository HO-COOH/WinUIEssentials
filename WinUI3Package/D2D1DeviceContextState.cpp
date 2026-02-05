#include "pch.h"
#include "D2D1DeviceContextState.h"
#include <d2d1_1.h>

D2D1DeviceContextState::D2D1DeviceContextState(ID2D1DeviceContext* d2dContext) : m_d2dContext{ d2dContext }
{
	d2dContext->GetTransform(&m_originalTransform);
	d2dContext->GetTarget(m_originalTarget.put());
}

D2D1DeviceContextState::~D2D1DeviceContextState()
{
	m_d2dContext->SetTarget(m_originalTarget.get());
	m_d2dContext->SetTransform(m_originalTransform);
}