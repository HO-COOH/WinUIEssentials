#pragma once
#include <array>
#include <utility>
#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include "TeachingTipTail.h"

class TeachingTipOutline
{
public:
	winrt::Windows::Foundation::Rect body{}; //The center line of the body border, ContentRootGrid's bounds inset by half of the stroke
	winrt::Microsoft::UI::Xaml::CornerRadius cornerRadius{};	//ContentRootGrid's corner radius inset by half of the stroke
	TeachingTipTail tail;
	float strokeThickness{};
	winrt::Windows::Foundation::Rect bodyAcrylic{}; //Where the body acrylic is, which is inside ContentRootGrid's border

	bool operator==(TeachingTipOutline const&) const = default;

	winrt::Microsoft::UI::Xaml::Media::Geometry CreateGeometry() const;

	constexpr winrt::Windows::Foundation::Rect CreateClip() const noexcept
	{
		//The tail acrylic is above ContentRootGrid, so clip off its half inside the body where it would cover the content.
		//The clip overlaps the edge of the body acrylic slightly to hide its soft edge, which is fine because both acrylics sample what is behind the window, not each other.
		//The other sides keep a margin so the antialiased edges of the tail are not cut
		constexpr auto antialiasingMargin = 1.f;
		float const tailLeft = (std::min)({ tail.apex.X, tail.base[0].X, tail.base[1].X }) - antialiasingMargin;
		float const tailTop = (std::min)({ tail.apex.Y, tail.base[0].Y, tail.base[1].Y }) - antialiasingMargin;
		float const tailRight = (std::max)({ tail.apex.X, tail.base[0].X, tail.base[1].X }) + antialiasingMargin;
		float const tailBottom = (std::max)({ tail.apex.Y, tail.base[0].Y, tail.base[1].Y }) + antialiasingMargin;
		constexpr auto rectFromSides = [](float left, float top, float right, float bottom)
		{
			return winrt::Windows::Foundation::Rect
			{ 
				left, 
				top, 
				(std::max)(0.f, right - left), 
				(std::max)(0.f, bottom - top) 
			};
		};

		switch (tail.side)
		{
			case TeachingTipTailSide::Top: return rectFromSides(tailLeft, tailTop, tailRight, bodyAcrylic.Y + antialiasingMargin);
			case TeachingTipTailSide::Right: return rectFromSides(bodyAcrylic.X + bodyAcrylic.Width - antialiasingMargin, tailTop, tailRight, tailBottom);
			case TeachingTipTailSide::Bottom: return rectFromSides(tailLeft, bodyAcrylic.Y + bodyAcrylic.Height - antialiasingMargin, tailRight, tailBottom);
			case TeachingTipTailSide::Left: return rectFromSides(tailLeft, tailTop, bodyAcrylic.X + antialiasingMargin, tailBottom);
		}
	}
private:
	//The radius of the corner after side when walking clockwise
	constexpr float cornerRadiusAfterSide(TeachingTipTailSide side) const noexcept
	{
		switch (side)
		{
			case TeachingTipTailSide::Top:		return static_cast<float>(cornerRadius.TopRight);
			case TeachingTipTailSide::Right:	return static_cast<float>(cornerRadius.BottomRight);
			case TeachingTipTailSide::Bottom:	return static_cast<float>(cornerRadius.BottomLeft);
			case TeachingTipTailSide::Left:		return static_cast<float>(cornerRadius.TopLeft);
		}
	}

	//The {start, end} of the straight part of each side between its corners when walking clockwise, indexed by TeachingTipTailSide
	constexpr std::array<std::pair<winrt::Windows::Foundation::Point, winrt::Windows::Foundation::Point>, 4> getSideRanges() const noexcept
	{
		float const left = body.X;
		float const top = body.Y;
		float const right = body.X + body.Width;
		float const bottom = body.Y + body.Height;

		return 
		{ {
			//Top
			{
				{ left + static_cast<float>(cornerRadius.TopLeft), top },
				{ right - static_cast<float>(cornerRadius.TopRight), top }
			},
			//Right
			{
				{ right, top + static_cast<float>(cornerRadius.TopRight) },
				{ right, bottom - static_cast<float>(cornerRadius.BottomRight) }
			},
			//Bottom
			{
				{ right - static_cast<float>(cornerRadius.BottomRight), bottom },
				{ left + static_cast<float>(cornerRadius.BottomLeft), bottom }
			},
			//Left
			{
				{ left, bottom - static_cast<float>(cornerRadius.BottomLeft) },
				{ left, top + static_cast<float>(cornerRadius.TopLeft) }
			}
		} };
	}

	std::array<winrt::Microsoft::UI::Xaml::Media::PathSegment, 10> createPathSegments() const;
	winrt::Microsoft::UI::Xaml::Media::PathFigure createPathFigure() const; 
};
