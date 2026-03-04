#include "pch.h"
#include "CombinedWallpaper.h"


bool CombinedWallpaper::createNewBitmapIfSizeChanged(ID2D1DeviceContext* d2dContext)
{
	auto const currentSize = D2D1::SizeU(
		GetSystemMetricsForDpi(SM_CXVIRTUALSCREEN, 96),
		GetSystemMetricsForDpi(SM_CYVIRTUALSCREEN, 96)
	);

	if (m_currentSize == currentSize)
		return false;

	auto combinedWallpaperProperties = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS::D2D1_BITMAP_OPTIONS_TARGET,
		D2D1::PixelFormat(DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE::D2D1_ALPHA_MODE_PREMULTIPLIED)
	);
	winrt::check_hresult(d2dContext->CreateBitmap(
		currentSize,
		nullptr,
		0,
		&combinedWallpaperProperties,
		m_combinedWallpaperBitmap.put()
	));
	m_currentSize = currentSize;

	return true;
}

void CombinedWallpaper::drawBitmapImpl(ID2D1DeviceContext* d2dContext, ID2D1Bitmap* bitmap, D2D1_RECT_F rect)
{
	d2dContext->DrawBitmap(bitmap, rect);
}

void CombinedWallpaper::Reset()
{
	m_currentSize = {};
}

void CombinedWallpaper::draw_span(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo)
{
	auto wallpaperBitmap = createBitmap(d2dContext, wallpaperInfo.wallpaper.get());
	auto const wallpaperSize = wallpaperBitmap->GetPixelSize();
	float const width = static_cast<float>(m_currentSize.width);
	float const height = static_cast<float>(m_currentSize.height);
	auto const scaleX = width / wallpaperSize.width;
	auto const scaleY = height / wallpaperSize.height;
	auto const finalScale = (std::max)(scaleX, scaleY);

	auto const destWidth = wallpaperSize.width * finalScale;
	auto const destHeight = wallpaperSize.height * finalScale;

	auto const destLeft = (width - destWidth) / 2.0f;
	auto const destTop = (height - destHeight) / 2.0f;

	drawBitmapImpl(d2dContext, wallpaperBitmap.get(), D2D1::RectF(destLeft, destTop, destLeft + destWidth, destTop + destHeight));
}

void CombinedWallpaper::draw_fill(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaperBitmap)
{
	auto const wallpaperSize = wallpaperBitmap->GetPixelSize();
	auto const rectWidth = static_cast<float>(wallpaperInfo.rect.right - wallpaperInfo.rect.left);
	auto const rectHeight = static_cast<float>(wallpaperInfo.rect.bottom - wallpaperInfo.rect.top);

	auto const scaleX = rectWidth / wallpaperSize.width;
	auto const scaleY = rectHeight / wallpaperSize.height;
	auto const finalScale = (std::max)(scaleX, scaleY);

	auto const destWidth = wallpaperSize.width * finalScale;
	auto const destHeight = wallpaperSize.height * finalScale;

	auto const destLeft = wallpaperInfo.rect.left + (rectWidth - destWidth) / 2.0f;
	auto const destTop = wallpaperInfo.rect.top + (rectHeight - destHeight) / 2.0f;

	d2dContext->PushAxisAlignedClip(
		D2D1::RectF(
			static_cast<float>(wallpaperInfo.rect.left),
			static_cast<float>(wallpaperInfo.rect.top),
			static_cast<float>(wallpaperInfo.rect.right),
			static_cast<float>(wallpaperInfo.rect.bottom)
		),
		D2D1_ANTIALIAS_MODE_PER_PRIMITIVE
	);

	drawBitmapImpl(d2dContext, wallpaperBitmap, D2D1::RectF(destLeft, destTop, destLeft + destWidth, destTop + destHeight));
	d2dContext->PopAxisAlignedClip();
}

void CombinedWallpaper::draw_tile(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper)
{
	winrt::com_ptr<ID2D1BitmapBrush> tileBrush;
	winrt::check_hresult(d2dContext->CreateBitmapBrush(wallpaper, tileBrush.put()));
	tileBrush->SetExtendModeX(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_WRAP);
	tileBrush->SetExtendModeY(D2D1_EXTEND_MODE::D2D1_EXTEND_MODE_WRAP);
	tileBrush->SetTransform(D2D1::Matrix3x2F::Translation(wallpaperInfo.rect.left, wallpaperInfo.rect.top));
	d2dContext->FillRectangle(D2D1::RectF(wallpaperInfo.rect.left, wallpaperInfo.rect.top, wallpaperInfo.rect.right, wallpaperInfo.rect.bottom), tileBrush.get());
}

void CombinedWallpaper::draw_center(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper)
{
	auto const wallpaperSize = wallpaper->GetPixelSize();
	auto const left = (std::min<float>)(wallpaperInfo.rect.left, (wallpaperInfo.rect.right + wallpaperInfo.rect.left - wallpaperSize.width) / 2);
	auto const right = (std::max<float>)(wallpaperInfo.rect.right, (wallpaperInfo.rect.right + wallpaperInfo.rect.left + wallpaperSize.width) / 2);
	auto const top = (std::min<float>)(wallpaperInfo.rect.top, (wallpaperInfo.rect.top + wallpaperInfo.rect.bottom - wallpaperSize.height) / 2);
	auto const bottom = (std::max<float>)(wallpaperInfo.rect.bottom, (wallpaperInfo.rect.top + wallpaperInfo.rect.bottom - wallpaperSize.height) / 2);
	drawBitmapImpl(d2dContext, wallpaper, D2D1::RectF(left, top, right, bottom));
}

void CombinedWallpaper::draw_stretch(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper)
{
	drawBitmapImpl(d2dContext, wallpaper, D2D1::RectF(wallpaperInfo.rect.left, wallpaperInfo.rect.top, wallpaperInfo.rect.right, wallpaperInfo.rect.bottom));
}

void CombinedWallpaper::draw_fit(ID2D1DeviceContext* d2dContext, WallpaperInfo const& wallpaperInfo, ID2D1Bitmap1* wallpaper)
{
	auto const wallpaperSize = wallpaper->GetPixelSize();
	auto const rectWidth = static_cast<float>(wallpaperInfo.rect.right - wallpaperInfo.rect.left);
	auto const rectHeight = static_cast<float>(wallpaperInfo.rect.bottom - wallpaperInfo.rect.top);

	auto const scaleX = rectWidth / wallpaperSize.width;
	auto const scaleY = rectHeight / wallpaperSize.height;
	auto const finalScale = (std::min)(scaleX, scaleY);

	auto const destWidth = wallpaperSize.width * finalScale;
	auto const destHeight = wallpaperSize.height * finalScale;

	auto const destLeft = wallpaperInfo.rect.left + (rectWidth - destWidth) / 2.0f;
	auto const destTop = wallpaperInfo.rect.top + (rectHeight - destHeight) / 2.0f;

	drawBitmapImpl(d2dContext, wallpaper, D2D1::RectF(destLeft, destTop, destLeft + destWidth, destTop + destHeight));
}

winrt::com_ptr<ID2D1Bitmap1> CombinedWallpaper::createBitmap(ID2D1DeviceContext* d2dContext, IWICFormatConverter* converter)
{
	winrt::com_ptr<ID2D1Bitmap1> wallpaperBitmap;
	//Todo: if size if weird, use another overload
	winrt::check_hresult(d2dContext->CreateBitmapFromWicBitmap(converter, wallpaperBitmap.put()));
	return wallpaperBitmap;
}


