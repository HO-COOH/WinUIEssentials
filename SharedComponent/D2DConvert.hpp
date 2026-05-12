#pragma once
#include <d2d1.h>

namespace D2DConvert
{
	constexpr inline auto ToD2DColor(winrt::Windows::UI::Color color)
	{
		auto const max = static_cast<float>(0xFF);
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
}