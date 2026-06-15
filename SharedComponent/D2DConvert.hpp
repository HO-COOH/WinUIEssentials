#pragma once
#include <d2d1.h>
#include <cmath>

namespace D2DConvert
{
	constexpr inline auto ToD2DColor(winrt::Windows::UI::Color color)
	{
		constexpr auto max = static_cast<float>(0xFF);
		return D2D_COLOR_F
		{
			.r = color.R / max,
			.g = color.G / max,
			.b = color.B / max,
			.a = color.A / max
		};
	}

	constexpr inline auto ToDWriteFontWeight(winrt::Windows::UI::Text::FontWeight fontWeight)
	{
		return static_cast<DWRITE_FONT_WEIGHT>(fontWeight.Weight);
	}

	inline RECT ToRect(D2D_RECT_F const& rect)
	{
		return RECT
		{
			.left   = static_cast<LONG>(std::floor(rect.left)),
			.top    = static_cast<LONG>(std::floor(rect.top)),
			.right  = static_cast<LONG>(std::ceil(rect.right)),
			.bottom = static_cast<LONG>(std::ceil(rect.bottom))
		};
	}

	constexpr inline auto ToDWriteHorizontalAlignment(winrt::WinUINamespace::UI::Xaml::HorizontalAlignment horizontalAlignment)
	{
		switch (horizontalAlignment)
		{
			case winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Left: return DWRITE_TEXT_ALIGNMENT_LEADING;
			case winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Center: return DWRITE_TEXT_ALIGNMENT_CENTER;
			case winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Right: return DWRITE_TEXT_ALIGNMENT_TRAILING;
			case winrt::WinUINamespace::UI::Xaml::HorizontalAlignment::Stretch: return DWRITE_TEXT_ALIGNMENT_JUSTIFIED;
		}
	}

	constexpr inline auto ToDwriteFontStyle(winrt::Windows::UI::Text::FontStyle fontStyle)
	{
		switch (fontStyle)
		{
			case winrt::Windows::UI::Text::FontStyle::Normal: return DWRITE_FONT_STYLE_NORMAL;
			case winrt::Windows::UI::Text::FontStyle::Oblique: return DWRITE_FONT_STYLE_OBLIQUE;
			case winrt::Windows::UI::Text::FontStyle::Italic: return DWRITE_FONT_STYLE_ITALIC;
		}
	}

	constexpr inline auto ToDwriteFontStretch(winrt::Windows::UI::Text::FontStretch fontStretch)
	{
		switch (fontStretch)
		{
			case winrt::Windows::UI::Text::FontStretch::Undefined: return DWRITE_FONT_STRETCH_UNDEFINED;
			case winrt::Windows::UI::Text::FontStretch::UltraCondensed: return DWRITE_FONT_STRETCH_ULTRA_CONDENSED;
			case winrt::Windows::UI::Text::FontStretch::ExtraCondensed: return DWRITE_FONT_STRETCH_EXTRA_CONDENSED;
			case winrt::Windows::UI::Text::FontStretch::Condensed: return DWRITE_FONT_STRETCH_CONDENSED;
			case winrt::Windows::UI::Text::FontStretch::SemiCondensed: return DWRITE_FONT_STRETCH_SEMI_CONDENSED;
			case winrt::Windows::UI::Text::FontStretch::Normal: return DWRITE_FONT_STRETCH_NORMAL;
			case winrt::Windows::UI::Text::FontStretch::SemiExpanded: return DWRITE_FONT_STRETCH_SEMI_EXPANDED;
			case winrt::Windows::UI::Text::FontStretch::Expanded: return DWRITE_FONT_STRETCH_EXPANDED;
			case winrt::Windows::UI::Text::FontStretch::ExtraExpanded: return DWRITE_FONT_STRETCH_EXTRA_EXPANDED;
			case winrt::Windows::UI::Text::FontStretch::UltraExpanded: return DWRITE_FONT_STRETCH_ULTRA_EXPANDED;
		}
	}
}