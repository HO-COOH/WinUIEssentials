#pragma once
#include <d2d1.h>
#include <dwrite.h>

struct TableData
{
	constexpr static inline float DefaultHeaderFontSize = 16.f;
	constexpr static inline float DefaultContentFontSize = 14.f;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultHeaderFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultContentFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline winrt::WinUINamespace::UI::Xaml::Thickness DefaultContentPadding{ 4.0,4.0,4.0,4.0 };
	constexpr static inline D2D_COLOR_F DefaultHeaderBackground = { 0 }; //Transparent


	D2D_COLOR_F m_headerForeground;
	D2D_COLOR_F m_contentForeground;
	D2D_COLOR_F m_headerBackground = DefaultHeaderBackground;

	float m_headerFontSize = DefaultHeaderFontSize;
	float m_contentFontSize = DefaultContentFontSize;
	DWRITE_TEXT_ALIGNMENT HeaderHorizontalAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT HeaderVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	D2D_COLOR_F m_horizontalLineColor;
	D2D_COLOR_F m_verticalLineColor = {};

	DWRITE_FONT_WEIGHT m_headerFontWeight;
	DWRITE_FONT_WEIGHT m_contentFontWeight;

	constexpr void InitializeForTheme(winrt::WinUINamespace::UI::Xaml::ElementTheme theme)
	{
		if (theme == winrt::WinUINamespace::UI::Xaml::ElementTheme::Light)
		{
			m_headerForeground = { 0.f, 0.f, 0.f, 1.f };
			m_contentForeground = { 0.f, 0.f, 0.f, 1.f };
			m_horizontalLineColor = { 0.f, 0.f, 0.f, 1.f };
		}
		else
		{
			m_headerForeground = { 1.f, 1.f, 1.f, 1.f };
			m_contentForeground = { 1.f, 1.f, 1.f, 1.f };
			m_horizontalLineColor = { 1.f, 1.f, 1.f, 1.f };
		}
	}

	winrt::WinUINamespace::UI::Xaml::Thickness m_contentPadding = DefaultContentPadding;
};