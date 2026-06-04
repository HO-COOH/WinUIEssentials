#pragma once
#include <winrt/base.h>
#include <d2d1_1.h>

//Offscreen cache of the rendered header row, saving a redraw in scrolling
class TableHeaderBitmap
{
protected:
	winrt::com_ptr<ID2D1Bitmap1> m_headerBitmap;
	UINT32 m_rawWidth{};
	UINT32 m_rawHeight{};
public:
	ID2D1Bitmap1* RecreateIfNeeded(ID2D1DeviceContext* d2dContext, UINT32 width, UINT32 height);
	ID2D1Bitmap1* Get() const
	{
		return m_headerBitmap.get();
	}
	operator bool() const noexcept
	{
		return static_cast<bool>(m_headerBitmap.get());
	}
};