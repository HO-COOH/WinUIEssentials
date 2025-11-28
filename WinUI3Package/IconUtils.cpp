#include "pch.h"
#include "IconUtils.h"
#include "GdiInitializeHelper.h"
#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <ShellScalingApi.h>
#pragma comment(lib, "shcore.lib") //For GetDpiForMonitor()

static inline void checkGdiplusStatus(Gdiplus::Status status)
{
	winrt::check_bool(status == Gdiplus::Status::Ok);
}

HICON Utils::GetHIcon(std::wstring_view file)
{
	GdiInitializeHelper::Initialize();
	
	HICON hicon{};

	Gdiplus::Image iconImage{ file.data() };
	INT const width = iconImage.GetWidth();
	INT const height = iconImage.GetHeight();

	Gdiplus::Bitmap bitmap{ width, height };
	auto graphics = Gdiplus::Graphics::FromImage(&bitmap);

	graphics->Clear(Gdiplus::Color::Transparent);
	graphics->DrawImage(&iconImage, 0, 0, width, height);

	checkGdiplusStatus(bitmap.GetHICON(&hicon));

	return winrt::check_pointer(hicon);
}

UINT Utils::GetPrimaryMonitorDpi()
{
	UINT x, y;
	winrt::check_hresult(GetDpiForMonitor(MonitorFromPoint({}, MONITOR_DEFAULTTOPRIMARY), MONITOR_DPI_TYPE::MDT_EFFECTIVE_DPI, &x, &y));
	return x;
}

HICON Utils::GetHIcon(winrt::Windows::Foundation::Uri uri)
{
	return HICON();
}

static HBITMAP drawGlyphImpl(std::wstring_view glyphString, Gdiplus::Bitmap&& bitmap, Gdiplus::Font&& font, Gdiplus::Brush& brush)
{
	auto graphics = winrt::check_pointer(Gdiplus::Graphics::FromImage(&bitmap));
	graphics->DrawString(glyphString.data(), -1, &font, {}, &brush);

	HBITMAP hBitmap{};
	checkGdiplusStatus(bitmap.GetHBITMAP(Gdiplus::Color::Black, &hBitmap));
	return winrt::check_pointer(hBitmap);
}

HBITMAP Utils::DrawGlyph(std::wstring_view glyphString, Gdiplus::Brush& brush, UINT dpi)
{
	GdiInitializeHelper::Initialize();

	std::optional<Gdiplus::FontFamily> fontFamily{ PrimaryGlyphFontFamily };
	if (!fontFamily->IsAvailable())
	{
		fontFamily.reset();
		fontFamily.emplace(FallbackGlyphFontFamily);
		assert(fontFamily->IsAvailable());
	}
	return drawGlyphImpl(
		glyphString,
		Gdiplus::Bitmap{ scaledMenuItemBitmapSize(dpi), scaledMenuItemBitmapSize(dpi) },
		Gdiplus::Font{ &*fontFamily, GlyphSize },
		brush);
}

HBITMAP Utils::DrawGlyph(std::wstring_view fontFamily, std::wstring_view glyphString, Gdiplus::Brush& brush, UINT dpi)
{
	GdiInitializeHelper::Initialize();

	Gdiplus::FontFamily gdiFontFamily{ fontFamily.data() };
	return drawGlyphImpl(
		glyphString,
		Gdiplus::Bitmap{ scaledMenuItemBitmapSize(dpi), scaledMenuItemBitmapSize(dpi) },
		Gdiplus::Font{ &gdiFontFamily, GlyphSize },
		brush
	);
}