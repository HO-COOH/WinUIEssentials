#pragma once
#include <string_view>
#include <winrt/Microsoft.UI.Xaml.h>

#pragma region Forward declaration
namespace Gdiplus
{
	class Brush;
}
#pragma endregion

class Utils
{
	constexpr static auto MenuItemBitmapSize = 16;
	constexpr static auto PrimaryGlyphFontFamily = L"Segoe Fluent Icons";
	constexpr static auto FallbackGlyphFontFamily = L"Segoe MDL2 Assets";
	constexpr static auto GlyphSize = 10;

public:
	static HICON GetHIcon(std::wstring_view path);

	//Draw for SymbolIcon, which uses Segoe Fluent Icon, fallback to Segoe MDL2 Assets if not exist
	static HBITMAP DrawGlyph(std::wstring_view glyphString, Gdiplus::Brush& brush, UINT dpi);

	//Draw for FontIcon
	static HBITMAP DrawGlyph(std::wstring_view fontFamily, std::wstring_view glyphString, Gdiplus::Brush& brush, UINT dpi);

	/**
	 * Get Dpi for primary monitor.
	 * @details It's because tray icon will only show on the primary monitor,
	 * therefore all the drawing only needs to consider the dpi of the primary monitor.
	 */
	static UINT GetPrimaryMonitorDpi();

	/**
	 * constexpr function for calculating dpi value
	 */
	template<typename T>
	static constexpr T ScaleForDpi(T value, UINT dpi)
	{
		return value * (dpi / 96.0);
	}

private:
	constexpr static auto scaledMenuItemBitmapSize(UINT dpi)
	{
		return ScaleForDpi(MenuItemBitmapSize, dpi);
	}
};

