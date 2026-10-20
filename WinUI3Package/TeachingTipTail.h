#pragma once
#include <array>
#include <dcommon.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>
#include "TeachingTipTailSide.hpp"

//Where the tail of a TeachingTip is, read from its TailPolygon.
//The diagrams in TeachingTipAcrylicStyle.cpp explain the math, see "2." for the constructor
class TeachingTipTail
{
public:
	TeachingTipTailSide side{};
	winrt::Windows::Foundation::Point apex{};
	winrt::Windows::Foundation::Point base[2]{};

	TeachingTipTail() = default;

	//bodyOutline is the center line of the body border, which the base corners are placed on
	TeachingTipTail(
		winrt::Microsoft::UI::Xaml::Shapes::Polygon const& tailPolygon,
		winrt::Microsoft::UI::Xaml::UIElement const& relativeTo,
		winrt::Windows::Foundation::Rect bodyOutline
	);

	bool operator==(TeachingTipTail const&) const = default;
private:
	void findApexAndSideFromTriangle(std::array<winrt::Windows::Foundation::Point, 3> triangle, D2D1_RECT_F bodyOutline);
	void alignBaseToBodyOutline(D2D1_RECT_F bodyOutline);

	constexpr bool isClockwise() const noexcept
	{
		switch (side)
		{
			case TeachingTipTailSide::Top:		return base[0].X < base[1].X;
			case TeachingTipTailSide::Right:	return base[0].Y < base[1].Y;
			case TeachingTipTailSide::Bottom:	return base[0].X > base[1].X;
			case TeachingTipTailSide::Left:		return base[0].Y > base[1].Y;
		}
	}

	constexpr float getSideLine(D2D1_RECT_F bodyOutline) const noexcept
	{
		switch (side)
		{
			case TeachingTipTailSide::Top:		return bodyOutline.top;
			case TeachingTipTailSide::Right:	return bodyOutline.right;
			case TeachingTipTailSide::Bottom:	return bodyOutline.bottom;
			case TeachingTipTailSide::Left:		return bodyOutline.left;
		}
	}

	constexpr bool isIntersectHorizontal() const noexcept
	{
		return side == TeachingTipTailSide::Top || side == TeachingTipTailSide::Bottom;
	}
};
