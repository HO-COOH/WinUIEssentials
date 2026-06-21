#pragma once
#include "TableHeaderBitmap.h"

struct ID2D1DeviceContext;

class TableVerticalLines : public TableHeaderBitmap
{
	uint32_t m_widthVersion{};
	bool m_dirty{};
public:
	//Draws the cached column-divider bitmap into the current target.
	//`bottom` clamps the destination to the data extent so dividers do not
	//extend below the last row when content is shorter than the viewport.
	void Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetX, float bottom);

	//partial draw, used by TableD2DContent::drawPartialHover()
	void Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetX, float top, float bottom);
	
	[[nodiscard]] bool CompareVersion(uint32_t widthVersion);
	
	constexpr void Invalidate()
	{
		m_dirty = true;
	}
};