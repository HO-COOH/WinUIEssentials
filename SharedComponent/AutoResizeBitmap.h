#pragma once
#include <winrt/base.h>
#include <d2d1_1.h>

//Offscreen cache of the rendered header row, saving a redraw in scrolling
class AutoResizeBitmap
{
protected:
	winrt::com_ptr<ID2D1Bitmap1> m_bitmap;
	D2D1_SIZE_U m_size;
public:
	ID2D1Bitmap1* RecreateIfNeeded(ID2D1DeviceContext* d2dContext, D2D1_SIZE_U size);
	ID2D1Bitmap1* RecreateIfNeeded(ID2D1DeviceContext* d2dContext, UINT32 width, UINT32 height);
	ID2D1Bitmap1* Get() const
	{
		return m_bitmap.get();
	}
	operator bool() const noexcept
	{
		return static_cast<bool>(m_bitmap.get());
	}

	constexpr void Reset() noexcept
	{
		m_size = {};
	}

	constexpr auto Size() const noexcept
	{
		return m_size;
	}
};