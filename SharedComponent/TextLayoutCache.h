#pragma once
#include <vector>
#include <winrt/base.h>
#include <dwrite.h>

class TextLayoutCache
{
	struct TextLayout
	{
		std::wstring content{};
		FLOAT maxWidth{};
		FLOAT maxHeight{};
		winrt::com_ptr<IDWriteTextLayout> layout;
	};

	std::vector<std::vector<TextLayout>> m_cache;
	IDWriteFactory* m_dwriteFactory{};

	//header text
	winrt::com_ptr<IDWriteTextFormat> m_headerTextFormat;
	winrt::com_ptr<IDWriteInlineObject> m_headerTrimming;

	//cell text
	winrt::com_ptr<IDWriteTextFormat> m_cellTextFormat;
	winrt::com_ptr<IDWriteInlineObject> m_cellTrimming;
public:
	TextLayoutCache(IDWriteFactory* dwriteFactory);

	void CreateHeaderTextFormat(
		WCHAR const* fontFamilyName,
		IDWriteFontCollection* fontCollection,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontStyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		WCHAR const* localeName
	);

	void CreateCeilTextFormat(
		WCHAR const* fontFamilyName,
		IDWriteFontCollection* fontCollection,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontStyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		WCHAR const* localeName
	);
	void Clear();

	IDWriteTextLayout* GetOrCreate(int row, int column, std::wstring_view str, FLOAT maxWidth, FLOAT maxHeight);
};