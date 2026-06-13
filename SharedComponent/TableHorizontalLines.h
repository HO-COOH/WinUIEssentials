#pragma once
#include <winrt/base.h>
#include <d2d1.h>

class TableD2DResource;
struct ID2D1DeviceContext;

// Caches the horizontal row-separator lines as a single-period path geometry
// covering one viewport. Because row height is uniform, vertical scrolling is
// a pure translation by fmod(scrollY, rowHeight) — no rebuild needed on scroll.
class TableHorizontalLines
{
	ID2D1Factory* m_d2dFactory;
	winrt::com_ptr<ID2D1PathGeometry> m_geometry;
	TableD2DResource& m_resource_ref;

	float m_viewportWidth = 0.f;
	float m_viewportHeight = 0.f;
	float m_rowHeight = 0.f;
	float m_headerHeight = 0.f;
public:

	TableHorizontalLines(ID2D1Factory* factory, TableD2DResource& resource);
	void Rebuild(float viewportWidth, float viewportHeight, float rowHeight, float headerHeight);
	// dataBottomY: device-pixel Y below which no line should appear (typically
	// the bottom of the last data row). Clips out the buffer line when data
	// doesn't extend past the viewport.
	void Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetY, float dataBottomY, float strokeWidth);
};
