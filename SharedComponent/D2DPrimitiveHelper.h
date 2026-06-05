#pragma once

struct ID2D1DeviceContext;
struct ID2D1Brush;
struct ID2D1StrokeStyle;
struct ID2D1GeometrySink;

namespace D2DPrimitiveHelper
{
	void DrawHorizontalLine(
		ID2D1DeviceContext* d2dContext,
		float startX,
		float endX,
		float y,
		ID2D1Brush* brush,
		float strokeWidth = 1.f,
		ID2D1StrokeStyle* strokeStyle = nullptr
	);

	void DrawHorizontalGeometry(
		ID2D1GeometrySink* sink,
		float startX,
		float endX,
		float y
	);

	void DrawVerticalLine(
		ID2D1DeviceContext* d2dContext,
		float x,
		float startY,
		float endY,
		ID2D1Brush* brush,
		float strokeWidth = 1.f,
		ID2D1StrokeStyle* strokeStyle = nullptr
	);
}
