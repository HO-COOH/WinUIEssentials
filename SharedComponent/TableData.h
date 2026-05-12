#pragma once
#include <d2d1.h>
#include <dwrite.h>

struct TableData
{
	constexpr static inline float DefaultHeaderFontSize = 16.f;
	constexpr static inline float DefaultContentFontSize = 14.f;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultHeaderFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultContentFontWeight = DWRITE_FONT_WEIGHT_NORMAL;

	D2D_COLOR_F m_headerForeground;
	D2D_COLOR_F m_headerHoveredForeground;
	float m_headerFontSize = DefaultHeaderFontSize;
	float m_contentFontSize = DefaultContentFontSize;
	DWRITE_TEXT_ALIGNMENT HeaderHorizontalAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT HeaderVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	DWRITE_FONT_WEIGHT m_headerFontWeight;
	DWRITE_FONT_WEIGHT m_contentFontWeight;


	constexpr static inline winrt::WinUINamespace::UI::Xaml::Thickness DefaultContentPadding{ 4.0,4.0,4.0,4.0 };

	winrt::WinUINamespace::UI::Xaml::Thickness m_contentPadding = DefaultContentPadding;
};