#include "pch.h"
#include "TableD2DResource.h"
#include <d2d1_1.h>

//C++20 synthesizes operator!= from this. Bitwise component comparison is
//fine here because the values come straight from cached storage, not from
//any arithmetic that could introduce rounding.
static inline bool operator==(D2D_COLOR_F const& a, D2D_COLOR_F const& b) noexcept
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

void TableD2DResource::Create(ID2D1DeviceContext* d2dContext, TableData&& tableData)
{
	if(tableData.m_headerForeground != m_localTableData.m_headerForeground) 
		winrt::check_hresult(d2dContext->CreateSolidColorBrush(tableData.m_headerForeground, m_textBrush.put()));
	
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x0F / static_cast<float>(0xFF)), m_backgroundBrush.put()));
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x2F / static_cast<float>(0xFF)), m_alternateBackgroundBrush.put()));
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x4cc2ff), m_pillBrush.put()));
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x103c4c), m_hoverBrush.put()));

	m_localTableData = std::move(tableData);
}
