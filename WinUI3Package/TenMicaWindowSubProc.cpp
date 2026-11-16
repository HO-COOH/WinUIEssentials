#include "pch.h"
#include "TenMicaWindowSubProc.hpp"

void TenMicaWindowSubProc::updateBorderPadding()
{
	m_borderPadding = GetSystemMetricsForDpi(SM_CXFRAME, m_dpi) + GetSystemMetricsForDpi(SM_CXPADDEDBORDER, m_dpi);
}

UINT TenMicaWindowSubProc::taskbarCreatedMessage()
{
	static UINT const msg = RegisterWindowMessageW(L"TaskbarCreated");
	return msg;
}
