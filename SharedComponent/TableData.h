#pragma once
#include <d2d1.h>
#include <dwrite.h>

struct TableData
{
	D2D_COLOR_F m_headerForeground;
	D2D_COLOR_F m_headerHoveredForeground;
	float m_headerFontSize;
	DWRITE_TEXT_ALIGNMENT HeaderHorizontalAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT HeaderVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	constexpr static inline winrt::WinUINamespace::UI::Xaml::Thickness DefaultContentPadding{ 4.0,4.0,4.0,4.0 };

	winrt::WinUINamespace::UI::Xaml::Thickness m_contentPadding = DefaultContentPadding;
};