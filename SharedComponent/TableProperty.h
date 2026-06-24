#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <vector>

struct TableProperty
{
	constexpr static inline float DefaultHeaderFontSize = 16.f;
	constexpr static inline float DefaultContentFontSize = 14.f;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultHeaderFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultContentFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline D2D_COLOR_F DefaultHeaderBackground = { 0 }; //Transparent

	constexpr static inline D2D_COLOR_F DefaultHeaderForegroundLight = { 0.f, 0.f, 0.f, 1.f };
	constexpr static inline D2D_COLOR_F DefaultContentForegroundLight = { 0.f, 0.f, 0.f, 1.f };

	constexpr static inline D2D_COLOR_F DefaultHeaderForegroundDark = { 1.f, 1.f, 1.f, 1.f };
	constexpr static inline D2D_COLOR_F DefaultContentForegroundDark = { 1.f, 1.f, 1.f, 1.f };

	D2D_COLOR_F m_headerForeground;
	D2D_COLOR_F m_contentForeground;
	D2D_COLOR_F m_headerBackground = DefaultHeaderBackground;
	D2D_COLOR_F m_pointerOverBackground;

	float m_headerFontSize = DefaultHeaderFontSize;
	float m_contentFontSize = DefaultContentFontSize;

	DWRITE_FONT_STYLE m_headerFontStyle = DWRITE_FONT_STYLE_NORMAL;
	DWRITE_FONT_STYLE m_contentFontStyle = DWRITE_FONT_STYLE_NORMAL;

	DWRITE_FONT_STRETCH m_headerFontStretch = DWRITE_FONT_STRETCH_NORMAL;
	DWRITE_FONT_STRETCH m_contentFontStretch = DWRITE_FONT_STRETCH_NORMAL;

	DWRITE_TEXT_ALIGNMENT HeaderHorizontalAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
	DWRITE_PARAGRAPH_ALIGNMENT HeaderVerticalAlignment = DWRITE_PARAGRAPH_ALIGNMENT::DWRITE_PARAGRAPH_ALIGNMENT_CENTER;

	D2D_COLOR_F m_horizontalLineColor = {};
	D2D_COLOR_F m_verticalLineColor = {};
	float m_horizontalLineThickness = 1.f;
	float m_verticalLineThickness = 1.f;

	DWRITE_FONT_WEIGHT m_headerFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	DWRITE_FONT_WEIGHT m_contentFontWeight = DWRITE_FONT_WEIGHT_NORMAL;

	struct AlternateRowColorPair
	{
		D2D_COLOR_F m_foreground;
		D2D_COLOR_F m_background;
	};
	std::vector<AlternateRowColorPair> m_alternateRowColors;

	constexpr void InitializeForTheme(winrt::WinUINamespace::UI::Xaml::ElementTheme theme)
	{
		if (theme == winrt::WinUINamespace::UI::Xaml::ElementTheme::Light)
		{
			m_headerForeground = DefaultHeaderForegroundLight;
			m_contentForeground = DefaultContentForegroundLight;
		}
		else
		{
			m_headerForeground = DefaultHeaderForegroundDark;
			m_contentForeground = DefaultContentForegroundDark;
		}
	}

	winrt::WinUINamespace::UI::Xaml::Thickness m_contentPadding{};
};