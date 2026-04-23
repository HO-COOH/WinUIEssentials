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
	IDWriteTextFormat* m_textFormat{};
	winrt::com_ptr<IDWriteInlineObject> m_trimming;
public:
	TextLayoutCache(IDWriteFactory* dwriteFactory);

	void SetFormat(IDWriteTextFormat* textFormat);
	IDWriteTextLayout* GetOrCreate(int row, int column, std::wstring_view str, FLOAT maxWidth, FLOAT maxHeight);
};