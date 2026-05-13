#include "pch.h"
#include "TableHeaderBitmap.h"

ID2D1Bitmap1* TableHeaderBitmap::RecreateIfNeeded(ID2D1DeviceContext* d2dContext, UINT32 width, UINT32 height)
{
	if (!m_headerBitmap || m_headerBitmapWidthPx != width || m_headerBitmapHeightPx != height)
	{
		D2D1_BITMAP_PROPERTIES1 const props
		{
			.pixelFormat = { DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED },
			.dpiX = 96.0f,
			.dpiY = 96.0f,
			.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET,
		};

		winrt::check_hresult(d2dContext->CreateBitmap(
			{ width, height },
			nullptr, 
			0, 
			&props, 
			m_headerBitmap.put()
		));
		m_headerBitmapWidthPx = width;
		m_headerBitmapHeightPx = height;
	}
	return m_headerBitmap.get();
}
