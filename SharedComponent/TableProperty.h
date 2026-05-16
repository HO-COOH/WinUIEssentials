#pragma once
#include <d2d1.h>
#include <dwrite.h>

struct TableProperty
{
	constexpr static inline float DefaultHeaderFontSize = 16.f;
	constexpr static inline float DefaultContentFontSize = 14.f;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultHeaderFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline DWRITE_FONT_WEIGHT DefaultContentFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
	constexpr static inline winrt::WinUINamespace::UI::Xaml::Thickness DefaultContentPadding{ 4.0,4.0,4.0,4.0 };
	constexpr static inline D2D_COLOR_F DefaultHeaderBackground = { 0 }; //Transparent

	constexpr static inline D2D_COLOR_F DefaultHeaderForegroundLight = { 0.f, 0.f, 0.f, 1.f };
	constexpr static inline D2D_COLOR_F DefaultContentForegroundLight = { 0.f, 0.f, 0.f, 1.f };
	constexpr static inline D2D_COLOR_F DefaultHorizontalLineColorLight = { 0.f, 0.f, 0.f, 1.f };

	constexpr static inline D2D_COLOR_F DefaultHeaderForegroundDark = { 1.f, 1.f, 1.f, 1.f };
	constexpr static inline D2D_COLOR_F DefaultContentForegroundDark = { 1.f, 1.f, 1.f, 1.f };
	constexpr static inline D2D_COLOR_F DefaultHorizontalLineColorDark = { 1.f, 1.f, 1.f, 1.f };

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
			m_headerForeground = DefaultHeaderForegroundLight;
			m_contentForeground = DefaultContentForegroundLight;
			m_horizontalLineColor = DefaultHorizontalLineColorLight;
		}
		else
		{
			m_headerForeground = DefaultHeaderForegroundDark;
			m_contentForeground = DefaultContentForegroundDark;
			m_horizontalLineColor = DefaultHorizontalLineColorDark;
		}
	}

	winrt::WinUINamespace::UI::Xaml::Thickness m_contentPadding = DefaultContentPadding;
};