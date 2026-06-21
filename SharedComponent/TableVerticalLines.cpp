#include "pch.h"
#include "TableVerticalLines.h"
#include <d2d1_1.h>
#include <algorithm>

void TableVerticalLines::Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetX, float bottom)
{
	auto const clampedBottom = std::clamp(bottom, 0.f, static_cast<float>(m_rawHeight));
	auto const src = D2D1::RectF(0.f, 0.f, static_cast<float>(m_rawWidth), clampedBottom);
	auto const dst = D2D1::RectF(scrollOffsetX, 0.f, scrollOffsetX + m_rawWidth, clampedBottom);
	d2dContext->DrawBitmap(
		m_headerBitmap.get(),
		dst,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		&src
	);
}

void TableVerticalLines::Draw(ID2D1DeviceContext* d2dContext, float scrollOffsetX, float top, float bottom)
{
	auto const src = D2D1::RectF(0.f, top, static_cast<float>(m_rawWidth), bottom);
	auto const dst = D2D1::RectF(scrollOffsetX, top, scrollOffsetX + m_rawWidth, bottom);
	d2dContext->DrawBitmap(
		m_headerBitmap.get(),
		dst,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		&src
	);
}

bool TableVerticalLines::CompareVersion(uint32_t widthVersion)
{
	return (std::exchange(m_widthVersion, widthVersion) != widthVersion) | std::exchange(m_dirty, false);
}
