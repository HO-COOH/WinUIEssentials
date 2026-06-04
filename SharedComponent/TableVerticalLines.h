#pragma once
#include "TableHeaderBitmap.h"

struct ID2D1DeviceContext;

class TableVerticalLines : public TableHeaderBitmap
{
	uint32_t m_widthVersion{};
public:
	void Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetX);
	//partial draw, used by TableD2DContent::drawPartialHover()
	void Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetX, float top, float bottom);
	[[nodiscard]] bool CompareVersion(uint32_t widthVersion);
};