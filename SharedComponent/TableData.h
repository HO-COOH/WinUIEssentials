#pragma once

struct TableData
{
	winrt::Windows::UI::Color m_headerForeground;
	winrt::Windows::UI::Color m_headerHoveredForeground;
	float m_headerFontSize;
	DWRITE_TEXT_ALIGNMENT HeaderHorizontalAlignment = DWRITE_TEXT_ALIGNMENT_CENTER;
	DWRITE_PARAGRAPH_ALIGNMENT HeaderVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
};