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
}