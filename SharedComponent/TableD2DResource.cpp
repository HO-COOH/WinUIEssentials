#include "pch.h"
#include "TableD2DResource.h"
#include <d2d1_1.h>
#include "TextLayoutCache.h"

//C++20 synthesizes operator!= from this. Bitwise component comparison is
//fine here because the values come straight from cached storage, not from
//any arithmetic that could introduce rounding.
static inline bool operator==(D2D_COLOR_F const& a, D2D_COLOR_F const& b) noexcept
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

TableD2DResource::TableD2DResource(TextLayoutCache& textLayoutCache) : m_textLayoutCache_ref{ textLayoutCache }
{
}

void TableD2DResource::Create(ID2D1DeviceContext* d2dContext, TableData&& tableData)
{
	if(tableData.m_headerForeground != m_localTableData.m_headerForeground) 
		winrt::check_hresult(d2dContext->CreateSolidColorBrush(tableData.m_headerForeground, m_headerTextBrush.put()));
	if (tableData.m_contentForeground != m_localTableData.m_contentForeground)
		winrt::check_hresult(d2dContext->CreateSolidColorBrush(tableData.m_contentForeground, m_contentTextBrush.put()));

	bool fontChanged{};
	if (tableData.m_headerFontSize != m_localTableData.m_headerFontSize || tableData.m_headerFontWeight != m_localTableData.m_headerFontWeight)
	{
		m_textLayoutCache_ref.CreateHeaderTextFormat(
			L"Segoe UI Semibold",
			nullptr,
			tableData.m_headerFontWeight,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			tableData.m_headerFontSize,
			L"en-US"
		);
		fontChanged = true;
	}

	if (tableData.m_contentFontSize != m_localTableData.m_contentFontSize || tableData.m_contentFontWeight != m_localTableData.m_contentFontWeight)
	{
		m_textLayoutCache_ref.CreateCeilTextFormat(
			L"Segoe UI",
			nullptr,
			tableData.m_contentFontWeight,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			tableData.m_contentFontSize,
			L"en-US"
		);
		fontChanged = true;
	}

	if (fontChanged)
		m_textLayoutCache_ref.Clear();

	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x0F / static_cast<float>(0xFF)), m_backgroundBrush.put()));
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 0x2F / static_cast<float>(0xFF)), m_alternateBackgroundBrush.put()));
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x4cc2ff), m_pillBrush.put()));
	winrt::check_hresult(d2dContext->CreateSolidColorBrush(D2D1::ColorF(0x103c4c), m_hoverBrush.put()));

	m_localTableData = std::move(tableData);
}

void TableD2DResource::ScaleChanged()
{
	m_textLayoutCache_ref.CreateHeaderTextFormat(
		L"Segoe UI Semibold",
		nullptr,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_localTableData.m_headerFontSize,
		L"en-US"
	);
	m_textLayoutCache_ref.CreateCeilTextFormat(
		L"Segoe UI",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		m_localTableData.m_contentFontSize,
		L"en-US"
	);
	m_textLayoutCache_ref.Clear();

}
