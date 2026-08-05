#include "pch.h"
#include "AutoResizeBitmap.h"

ID2D1Bitmap1* AutoResizeBitmap::RecreateIfNeeded(ID2D1DeviceContext* d2dContext, D2D1_SIZE_U size)
{
	if (m_bitmap && m_size == size)
		return m_bitmap.get();

	constexpr D2D1_BITMAP_PROPERTIES1 ColumnProperty
	{
		.pixelFormat = { DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED },
		.dpiX = 96.0f,
		.dpiY = 96.0f,
		.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET,
	};

	winrt::check_hresult(d2dContext->CreateBitmap(
		size,
		nullptr,
		0,
		&ColumnProperty,
		m_bitmap.put()
	));
	m_size = size;
	return m_bitmap.get();
}

ID2D1Bitmap1* AutoResizeBitmap::RecreateIfNeeded(ID2D1DeviceContext* d2dContext, UINT32 width, UINT32 height)
{
	return RecreateIfNeeded(d2dContext, { width, height });
}
