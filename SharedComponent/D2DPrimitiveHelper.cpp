#include "pch.h"
#include "D2DPrimitiveHelper.h"
#include <d2d1_1.h>

namespace D2DPrimitiveHelper
{
	void DrawHorizontalLine(
		ID2D1DeviceContext* d2dContext,
		float startX,
		float endX,
		float y,
		ID2D1Brush* brush,
		float strokeWidth,
		ID2D1StrokeStyle* strokeStyle
	)
	{
		d2dContext->DrawLine(
			D2D1::Point2F(startX, y),
			D2D1::Point2F(endX, y),
			brush,
			strokeWidth,
			strokeStyle
		);
	}

	void DrawVerticalLine(
		ID2D1DeviceContext* d2dContext, 
		float x, 
		float startY, 
		float endY, 
		ID2D1Brush* brush, 
		float strokeWidth, 
		ID2D1StrokeStyle* strokeStyle)
	{
		d2dContext->DrawLine(
			D2D1::Point2F(x, startY),
			D2D1::Point2F(x, endY),
			brush,
			strokeWidth,
			strokeStyle
		);
	}
}
